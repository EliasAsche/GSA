
import os
import json
import time
from pathlib import Path

import plaid
from dotenv import load_dotenv
from plaid.api import plaid_api
from plaid.model.products import Products
from plaid.model.sandbox_public_token_create_request import (
    SandboxPublicTokenCreateRequest,
)
from plaid.model.sandbox_public_token_create_request_options import (
    SandboxPublicTokenCreateRequestOptions,
)
from plaid.model.item_public_token_exchange_request import (
    ItemPublicTokenExchangeRequest,
)
from plaid.model.transactions_sync_request import (
    TransactionsSyncRequest,
)


# Project paths
PROJECT_DIR = Path(__file__).resolve().parent
TOKEN_FILE = PROJECT_DIR / ".local" / "plaid_sandbox_access_token.txt"


def get_access_token(client):
    """
    Reuse an existing Sandbox connection or create a new one.
    Access tokens are stored locally and excluded from Git.
    """

    if TOKEN_FILE.exists():
        access_token = TOKEN_FILE.read_text(
            encoding="utf-8"
        ).strip()

        if not access_token:
            raise RuntimeError("Saved Sandbox access token is empty.")

        print("Reusing existing Plaid Sandbox connection.")
        return access_token

    print("Creating new Plaid Sandbox connection...")

    # Create a simulated bank connection.
    request = SandboxPublicTokenCreateRequest(
        institution_id="ins_109508",
        initial_products=[Products("transactions")],
        options=SandboxPublicTokenCreateRequestOptions(
            override_username="user_transactions_dynamic",
            override_password="pass_good",
        ),
    )

    public_response = client.sandbox_public_token_create(request)

    # Exchange public token for an access token.
    exchange_request = ItemPublicTokenExchangeRequest(
        public_token=public_response["public_token"]
    )

    exchange_response = client.item_public_token_exchange(
        exchange_request
    )

    access_token = exchange_response["access_token"]

    # Store the access token locally.
    TOKEN_FILE.parent.mkdir(parents=True, exist_ok=True)
    TOKEN_FILE.write_text(access_token, encoding="utf-8")

    print("Sandbox connection established and saved locally.")

    return access_token


def fetch_transactions(client, access_token):
    """
    Retrieve transactions using Plaid's sync endpoint.
    Retry when a newly created Item has no data yet.
    """

    max_attempts = 8
    transactions = []

    for attempt in range(1, max_attempts + 1):
        transactions = []
        cursor = None

        # Retrieve all pages of available transactions.
        while True:
            sync_request = TransactionsSyncRequest(
                access_token=access_token,
                **({"cursor": cursor} if cursor else {}),
            )

            response = client.transactions_sync(sync_request)

            transactions.extend(response["added"])
            cursor = response["next_cursor"]

            if not response["has_more"]:
                break

        if transactions:
            break

        print(
            f"No transactions available yet "
            f"(attempt {attempt}/{max_attempts})."
        )

        if attempt < max_attempts:
            time.sleep(3)

    return transactions


def main():
    # Load local credentials.
    load_dotenv(PROJECT_DIR / ".env")

    client_id = os.getenv("PLAID_CLIENT_ID")
    secret = os.getenv("PLAID_SECRET")
    environment = os.getenv("PLAID_ENV")

    if not client_id or not secret:
        raise RuntimeError("Missing Plaid credentials in .env")

    if environment != "sandbox":
        raise RuntimeError("This script only supports Plaid Sandbox.")

    # Configure Plaid API client.
    configuration = plaid.Configuration(
        host=plaid.Environment.Sandbox,
        api_key={
            "clientId": client_id,
            "secret": secret,
            "plaidVersion": "2020-09-14",
        },
    )

    client = plaid_api.PlaidApi(
        plaid.ApiClient(configuration)
    )

    # Reuse or create a Sandbox connection.
    access_token = get_access_token(client)

    # Retrieve transaction history.
    transactions = fetch_transactions(client, access_token)

    print(f"\nRetrieved {len(transactions)} transactions.")

    # Display a small sample.
    for transaction in transactions[:5]:
        print(
            f"{transaction['date']} | "
            f"{transaction['name']} | "
            f"${transaction['amount']:.2f}"
        )

    if not transactions:
        print("Transaction history is not available yet.")


if __name__ == "__main__":
    try:
        main()

    except plaid.ApiException as error:
        try:
            details = json.loads(error.body)
            print(
                "Plaid API error:",
                details.get("error_code", "unknown"),
            )
        except (ValueError, TypeError):
            print("Plaid API request failed.")
