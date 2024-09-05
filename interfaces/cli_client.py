import argparse
import requests

BASE_URL = 'http://localhost:8848'

def store_value(key, value):
    url = f'{BASE_URL}/set'
    data = {'key': key, 'value': value}
    response = requests.post(url, json=data)
    print(response.text)

def retrieve_value(key):
    url = f'{BASE_URL}/get?key={key}'
    response = requests.get(url)
    if response.status_code == 200:
        print(response.json())
    else:
        print("Key not found")

def update_value(key, value):
    url = f'{BASE_URL}/patch?key={key}&value={value}'
    response = requests.patch(url)
    print(response.text)

def delete_value(key):
    url = f'{BASE_URL}/del?key={key}'
    response = requests.delete(url)
    print(response.text)

def delete_all():
    url = f'{BASE_URL}/flush'
    response = requests.delete(url)
    print(response.text)

def expire_key(key, seconds):
    url = f'{BASE_URL}/expire'
    data = {'key': key, 'seconds': seconds}
    response = requests.post(url, json=data)
    print(response.text)

def main():
    parser = argparse.ArgumentParser(description="CLI for interacting with Redis-Alternative")
    subparsers = parser.add_subparsers(dest="command")

    # Store value
    parser_store = subparsers.add_parser("store", help="Store a key-value pair")
    parser_store.add_argument("key", type=str, help="Key to store")
    parser_store.add_argument("value", type=str, help="Value to store")

    # Retrieve value
    parser_get = subparsers.add_parser("get", help="Retrieve the value of a key")
    parser_get.add_argument("key", type=str, help="Key to retrieve")

    # Update value
    parser_update = subparsers.add_parser("update", help="Update the value of a key")
    parser_update.add_argument("key", type=str, help="Key to update")
    parser_update.add_argument("value", type=str, help="New value")

    # Delete value
    parser_delete = subparsers.add_parser("delete", help="Delete a key-value pair")
    parser_delete.add_argument("key", type=str, help="Key to delete")

    # Delete all keys
    parser_flush = subparsers.add_parser("flush", help="Delete all keys")

    # Expire key
    parser_expire = subparsers.add_parser("expire", help="Expire a key in X seconds")
    parser_expire.add_argument("key", type=str, help="Key to expire")
    parser_expire.add_argument("seconds", type=int, help="Seconds until expiration")

    args = parser.parse_args()

    if args.command == "store":
        store_value(args.key, args.value)
    elif args.command == "get":
        retrieve_value(args.key)
    elif args.command == "update":
        update_value(args.key, args.value)
    elif args.command == "delete":
        delete_value(args.key)
    elif args.command == "flush":
        delete_all()
    elif args.command == "expire":
        expire_key(args.key, args.seconds)
    else:
        parser.print_help()

if __name__ == "__main__":
    main()