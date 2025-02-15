helloWorld = None
def printHelloWorld():
    global helloWorld
    print("Hello world! This function is in api/backend/helpers.py, and it is called in api/backend/apps.py")
    helloWorld = "Hello world"