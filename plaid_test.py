
import os
import json
import time

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
from plaid.model.transactions_sync_request import TransactionsSyncRequest


def main():
    # Load API credentials without hardcoding them.
    load_dotenv()

    client_id = os.getenv("PLAID_CLIENT_ID")
    secret = os.getenv("PLAID_SECRET")
    environment = os.getenv("PLAID_ENV")

    if not client_id or not secret:
        raise RuntimeError("Missing Plaid credentials in .env")

    if environment != "sandbox":
        raise RuntimeError("This test only supports Plaid Sandbox.")

    # Initialize the official Plaid Python SDK.
    configuration = plaid.Configuration(
        host=plaid.Environment.Sandbox,
        api_key={
            "clientId": client_id,
            "secret": secret,
            "plaidVersion": "2020-09-14",
        },
    )

    client = plaid_api.PlaidApi(plaid.ApiClient(configuration))

    # Create a simulated bank connection.
    print("Creating Plaid Sandbox connection...")

    request = SandboxPublicTokenCreateRequest(
        institution_id="ins_109508",
        initial_products=[Products("transactions")],
        options=SandboxPublicTokenCreateRequestOptions(
            override_username="user_transactions_dynamic",
            override_password="pass_good",
        ),
    )

    public_response = client.sandbox_public_token_create(request)

    # Exchange the temporary public token for an access token.
    exchange_request = ItemPublicTokenExchangeRequest(
        public_token=public_response["public_token"]
    )

    exchange_response = client.item_public_token_exchange(
        exchange_request
    )

    access_token = exchange_response["access_token"]
    print("Sandbox connection established successfully!")

    # Fetch transaction history, including paginated results.
    
    # Allow the newly created Sandbox Item to initialize.
    max_attempts = 8
    transactions = []

    for attempt in range(1, max_attempts + 1):
        transactions = []
        cursor = None

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

    print(f"\nRetrieved {len(transactions)} transactions.")

    for transaction in transactions[:5]:
        print(
            f"{transaction['date']} | "
            f"{transaction['name']} | "
            f"${transaction['amount']:.2f}"
        )

    if not transactions:
        print("Transaction history was not ready during this test.")


if __name__ == "__main__":
    try:
        main()
    except plaid.ApiException as error:
        try:
            details = json.loads(error.body)
            print("Plaid API error:", details.get("error_code", "unknown"))
        except (ValueError, TypeError):
            print("Plaid API request failed.")
