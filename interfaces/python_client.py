import requests

class KeyValueStoreClient:
    def __init__(self, base_url='http://localhost:5555'):
        self.base_url = base_url

    def store_value(self, key, value):
        url = f"{self.base_url}/set"
        data = {'key': key, 'value': value}
        response = requests.post(url, json=data)
        return response.text

    def retrieve_value(self, key):
        url = f"{self.base_url}/get?key={key}"
        response = requests.get(url)
        if response.status_code == 200:
            return response.json()
        else:
            return None

# Usage example
if __name__ == "__main__":
    client = KeyValueStoreClient()
    client.store_value('name', 'aditya')
    result = client.retrieve_value('name')
    print(result)
