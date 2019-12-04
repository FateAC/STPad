# -*- coding : utf-8 -*-

import requests
import os

def Convert(a):
    a = str(a//100) + '/' + str(a) + '.pdf'
    return a

def ProblemCrawler(proname, url_2):
    url = 'https://onlinejudge.org/external/'
    url = url + url_2
    print(url)
    doc = requests.get(url)
    doc_name = './problems/' + str(proname) + '.pdf'
    with open(doc_name, 'wb') as down_file :
        down_file.write(doc.content)

if __name__ == '__main__':
    proname = int(input().strip())
    if not os.path.exists('./problems') : os.mkdir('./problems')
    ProblemCrawler(proname, Convert(proname))
    
