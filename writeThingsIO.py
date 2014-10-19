import sys
import json
import requests

def generate_request(temperature, light):
    endpoint = "https://api.thethings.io/v1/ThingWrite"
    headers = {
       'Content-type': 'application/json', 
       'Authorization: theThingsIO-Token' : '33a2c3a662dab57b9c672bab22de295af101257f62b3d8227cfcf0efe4f23e18',
       'Accept': 'application/json'}
    data = {
       "thing": {
       "id": "1799c2e785660cae485e9f31385d857a75dc70c5ff2f49c0d35c4c3af894978b"
       },
       "values": [
       {
          "key": "temperature",
          "value": temperature,
          "units": "celsius",
          "type": "temporal"
       },
       {
          "key": "light",
          "value": light,
          "units": "luxes",
          "type": "temporal"
       }]
    }

    r = requests.post(endpoint, data=json.dumps(data), headers=headers, verify=False)
    
    print "REQUEST : POST " + endpoint
    print str(json.dumps(data))
    print "RESPONSE : "+ str(r.status_code)
    print r.text

def main():   

    if len(sys.argv) != 3:
         print 'usage: ./writeThingsIO.py temp_cel light_luxes'
         sys.exit(1)

    temperature = sys.argv[1]
    light = sys.argv[2]
    data = generate_request(temperature, light) 


if __name__ == '__main__':
    main()
    
 