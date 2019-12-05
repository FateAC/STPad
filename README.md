# STPad
## 簡介
- Is A IDE For Programming Contest
- 編寫語言：Qt(C++)，Python
- 開發人員：Adam7066，Kaixiang4515
## 功能
- 支援平台：Windows
- 支援語言：C/C++
- 自動上交程式碼
- 支援的Online Judge： [Uva](https://onlinejudge.org/)
- 一鍵代碼格式化，使用 [AStyle](http://astyle.sourceforge.net/)
    - 目前格式參數```--style=google --pad-oper --break-closing-braces```
- 模板功能：檔案位置為```%STPad%/plugins/Template/```，可自行更改
## 安裝
- [下載 STPad](https://github.com/STPad/STPad/releases/download/v1.0/STPad.zip)
- 解壓縮後，執行exe檔
- 自行安裝MinGW/g++，並將```%MinGW%/bin```加到Path中。
    - 檢查是否成功：開啟cmd，執行```g++ --version```
- [下載](https://chromedriver.chromium.org/downloads)對應Google Chrome版本的Chromedriver，並將chromedriver.exe放進```%STPad%/Python/CodeSubmit/```資料夾裡
