# Redis-Alternative
---

Redis-Alternative is a lightweight, high-performance key-value store designed to provide an alternative to Redis. It supports all the common Redis operations and is accessible via a RESTful API.

---

## Installation
To run the project, you have two options: setting up the Drogon environment on your machine or using the provided Docker image.

### Option 1: Setup Drogon Environment
Follow the resources below to set up the Drogon environment on your machine:
1. [Drogon Documentation](https://drogonframework.github.io/drogon-docs/#/)
2. [Abusing Server-Side Rendering in Drogon](https://trebledj.me/posts/abusing-server-side-rendering-in-drogon/)

### Option 2: Use Docker Image
Pull the Docker image from the following location:
[Docker Image](https://hub.docker.com/layers/aditya292002/redis-alternative/latest/images/sha256-c6bc62903ea830e51289022c3ce6e95d66c832e735ba1f061657d0a9d8e70e94?context=repo)

Then run the image using the command:
```sh
docker run -p 8848:8848 aditya292002/redis-alternative:latest
```

## Features
Here are the available features of Redis-Alternative:

### Set a Key-Value Pair
Send a POST request to `localhost:8848/set` with the data in JSON format. Example:

```json
{
    "key": "name",
    "value": "Joe"
}
```

### Get Value of a Key
Send a GET request to `localhost:8848/get` with the key as a query parameter. 
Example: `localhost:8848/get?key=name`

### Update Value of a Key
Send a PATCH request to `localhost:8848/patch` with the key and new value as query parameters. 
Example:
`localhost:8848/patch?key=name&value=adi`

### Delete a Key
Send a DELETE request to `localhost:8848/del` with the key as a query parameter. 
Example: `localhost:8848/del?key=name`

### Delete All Keys
Send a DELETE request to `localhost:8848/flush`. 
Example: `localhost:8848/flush`

### Expire a Key in X Seconds
Send a POST request to `localhost:8848/expire` with the data in JSON format. 
Example:

```json
{
    "key": "name",
    "seconds": 60
}
```

## Interfaces
- Python Client (python_client.py): Contains a class (KeyValueStoreClient) with methods to interact with your API (store_value and retrieve_value).
- CLI Client (cli_client.py): Uses argparse to provide a command-line interface. This file imports and uses the KeyValueStoreClient to handle the API requests based on user input.

## How to Run:
Python Client Usage:

```python
from interface.python_client import KeyValueStoreClient

client = KeyValueStoreClient()
client.store_value('name', 'aditya')
print(client.retrieve_value('name'))
```

CLI Client Usage:

```bash
python3 interface/cli_client.py store name --value aditya
python3 interface/cli_client.py retrieve name
```



 * Contact
 * For any questions or suggestions, please open an issue or contact the project maintainer.

 * Maintainer
 * Email: keshariaditya90@gmail.com
