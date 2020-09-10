import requests
import re


session = requests.Session()
    
def get_token():
    url = 'https://resources.calvin.edu/selfservice/WebAdvisor?TYPE=P&PID=ST-WESTS12A&LASTTOKEN=NULL&TOKENIDX=NULL'
    resp = session.get(url)
    return resp.cookies["LASTTOKEN"]

def get_data(token):
    r = session.post("https://resources.calvin.edu/selfservice/WebAdvisor?TOKENIDX={0}&SS=1&APP=ST".format(token),
                      data={"VAR1":"20/FA","DATE.VAR1":"","DATE.VAR2":"","LIST.VAR1_CONTROLLER":"LIST.VAR1","LIST.VAR1_MEMBERS":"LIST.VAR1*LIST.VAR2*LIST.VAR3*LIST.VAR4","LIST.VAR1_MAX":"5","LIST.VAR2_MAX":"5","LIST.VAR3_MAX":"5","LIST.VAR4_MAX":"5","LIST.VAR1_1":"","LIST.VAR2_1":"","LIST.VAR3_1":"","LIST.VAR4_1":"","LIST.VAR1_2":"","LIST.VAR2_2":"","LIST.VAR3_2":"","LIST.VAR4_2":"","LIST.VAR1_3":"","LIST.VAR2_3":"","LIST.VAR3_3":"","LIST.VAR4_3":"","LIST.VAR1_4":"","LIST.VAR2_4":"","LIST.VAR3_4":"","LIST.VAR4_4":"","LIST.VAR1_5":"","LIST.VAR2_5":"","LIST.VAR3_5":"","LIST.VAR4_5":"","VAR7":"","VAR8":"","VAR3":"","VAR6":"","VAR21":"","VAR9":"","RETURN.URL":"HTTP://www.calvin.edu/students","SUBMIT_OPTIONS":""}, verify=True)

    for response in r.history:
        print(response.url)

token = get_token()
        
print(token)
get_data(token)
