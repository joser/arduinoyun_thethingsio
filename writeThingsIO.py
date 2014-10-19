import sys
import json
import requests

# Generate json with temperature and light and POST it to TheThingsIO
def generate_request(temperature, light):
    endpoint = "https://api.thethings.io/v1/ThingWrite"
    headers = {
       'Content-type': 'application/json', 
       'Authorization: theThingsIO-Token' : 'xxxxxxxx',
       'Accept': 'application/json'}
    data = {
       "thing": {
       "id": "xxxxxxx"
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

# Get temperature and light from command line
def main():   

    if len(sys.argv) != 3:
         print 'usage: ./writeThingsIO.py temp_cel light_luxes'
         sys.exit(1)

    temperature = sys.argv[1]
    light = sys.argv[2]
    data = generate_request(temperature, light) 


if __name__ == '__main__':
    main()
    
 