# -*- coding : utf-8 -*-

from selenium import webdriver
import selenium.webdriver.support.ui as ui
from time import sleep

url = 'https://onlinejudge.org/'
submit_url = 'https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=25'
acc = ''
pwd = ''
proID = ''
file_path = ''
def Login():
    browser = webdriver.Chrome()
    browser.get(url)
    wait=ui.WebDriverWait(browser,10)
    wait.until(lambda browser: browser.find_element_by_id('mod_login_username'))
    
    acc_btn = browser.find_element_by_id('mod_login_username')
    pwd_btn = browser.find_element_by_id('mod_login_password')
    login_btn = browser.find_element_by_name('Submit')
    
    acc_btn.clear(); pwd_btn.clear()
    acc_btn.send_keys(acc); pwd_btn.send_keys(pwd)
    login_btn.click()
    #sleep(2)
    
    browser.get(submit_url)
    wait.until(lambda browser: browser.find_element_by_name('localid'))
    
    pro_btn = browser.find_element_by_name('localid')
    pro_btn.clear()
    pro_btn.send_keys(proID)
    lan_btn = browser.find_element_by_xpath('/html/body/div[2]/div/div[4]/div[3]/div[1]/div/form/table/tbody/tr[2]/td[2]/input[5]')
    lan_btn.click()
    upload_btn = browser.find_element_by_xpath('/html/body/div[2]/div/div[4]/div[3]/div[1]/div/form/table/tbody/tr[4]/td[2]/input').send_keys(file_path)
    sub_btn = browser.find_element_by_xpath('/html/body/div[2]/div/div[4]/div[3]/div[1]/div/form/table/tbody/tr[5]/td[2]/input[1]')
    sub_btn.click()
    
    wait.until(lambda browser: browser.find_element_by_name('localid'))
    
    #browser.get(url)
    #wait.until(lambda browser: browser.find_element_by_id('mod_login_username'))
    try:
        browser.close()
        browser.quit()
    except:
        browser.close()
        browser.quit()
    
    return
    

if __name__ == '__main__' :
    proID = input().strip()
    acc = input().strip()
    pwd = input().strip()
    file_path = input().strip()
    
    Login()