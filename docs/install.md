# 安裝指南


## Windows



### 使用VNStudio


#### 1.下載VNStudio （Python 3.7 64位）

VNStudio是vn.py團隊自行打包的一鍵安裝版本，整合了：
- Python 3.7（社群官方版本)
- vn.py框架和其他相關庫
- VN Station量化工作站（vn.py框架的圖形化管理工具）

下載地址：[vnstudio-2.1.1.exe](https://download.vnpy.com/vnstudio-2.1.1.exe)

&nbsp;


#### 2.安裝VNStudio

一路點選“下一步”即可完成VNStudio安裝，安裝完成後可以檢視相關執行目錄：

- VNStudio預設安裝路徑為C:\vnstudio；
- VNStudio預設json配置檔案和資料庫路徑為C:\Users\Administrator\\.vntrader
- VN Station量化工作站執行目錄為C:\vnstudio\Scripts\vnstation.exe；
- vnpy執行目錄在C:\vnstudio\Lib\site-packages\vnpy（進入該目錄後，使用者可以修改vnpy的相關功能）


&nbsp;

#### 3.登陸VNStation

輸入賬號密碼或者微信掃碼登陸VNStation。（社群賬號通過微信掃碼可得）

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/install.bat/login_VNConda.png "enter image title here")

&nbsp;

#### 4.使用VNStation
登入後會進入到VN Station的主介面。
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/install.bat/login_VNConda_2.png "enter image title here")

視窗下方有5個選項：
- VN Trade Lite：直接執行VN Trader (只有CTP介面)
- VN Trader Pro：先選擇儲存相關臨時檔案的目錄，再執行VN Trader (介面和上層應用模組任選)
- Jupyter Notebook：先選擇儲存相關臨時檔案的目錄，再執行Jupyter Notebook
- 提問求助：提出相關問題，管理員會每天定時回覆
- 後臺更新：一鍵更新VN Station


&nbsp;

#### 5.更新VNStation
更新VNStation除了“一鍵更新”外；也可以解除安裝老版本，安裝新版本；或者在github上下載最新的dev分支，解壓後得到根目錄下的vnpy資料夾，對C:\vnstudio\Lib\site-packages\vnpy進行替換。



&nbsp;
&nbsp;


### 手動安裝

#### 1.下載並安裝最新版Anaconda3.7 64位

下載地址如下：[Anaconda Distribution](https://www.anaconda.com/distribution/)

(更輕量的Miniconda地址：[MiniConda Distribution](https://docs.conda.io/en/latest/miniconda.html))

&nbsp;

#### 2.下載並解壓vnpy

進入vnpy的github主頁[vnpy](https://github.com/vnpy/vnpy)。
在左方的Branch選項，master對應是最新的穩定版本，dev對應的是最新測試版本；
然後在主頁右方綠色的clone or download選項，選擇Download ZIP來下載壓縮版本到本地電腦。

&nbsp;

#### 3.安裝vnpy
雙擊install.bat一鍵安裝vnpy：
- 先安裝ta_lib庫和ib api
- 然後安裝requirements.txt檔案內相關依賴庫
- 最後複製vnpy到Anaconda內

&nbsp;

#### 4.啟動VN Trader
在資料夾tests\trader中找到run.py檔案。按住“Shift” + 滑鼠右鍵進入cmd視窗，輸入下面命令即可啟動VN Trader。
```
python run.py 
```

&nbsp;
&nbsp;


## Ubuntu


### 1. 下載並安裝最新版本的Anaconda或者Miniconda （Python 3.7 64位）

以MiniConda為例，進入已下載好 Miniconda3-latest-Linux-x86_64.sh 所在目錄，終端執行如下命令開始安裝。
```
$ bash Miniconda3-latest-Linux-x86_64.sh
```

安裝過程中可以一直按“Enter”鍵繼續下去，除了以下這點：

當詢問是否把Miniconda設定為Python 預設環境時，把預設的"no"改成“yes”。原因是Ubuntu 18.04已有自帶的Python 3.6與Python 2.7。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/install.bat/install_Miniconda_ubuntu.png "enter image title here")



重啟Ubuntu後，開啟終端直接輸入"python" 然後按“Enter”鍵: 若出現如下圖，則表示成功把Miniconda設定為Python預設環境。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/install.bat/Conda_Python_version.png "enter image title here")

&nbsp;

### 2. 下載並解壓vnpy
Linux使用者選擇tar.gz壓縮版本。下載地址如下：[vnpy releases](https://github.com/vnpy/vnpy/releases)

&nbsp;

### 3. 安裝vnpy
先安裝gcc編譯器，用於編譯C++類介面檔案。在終端中輸入以下命令即可。
```
sudo apt-get  install  build-essential
```


然後在vnpy根目錄開啟終端，輸入下面命令一鍵安裝vnpy。
```
bash install.sh
```

安裝過程分為4步：
- 下載並安裝ta_lib庫和numpy
- 安裝requirements.txt檔案內相關依賴庫
- 安裝中文編碼（針對英文系統）
- 複製vnpy到Anaconda內（若是在虛擬機器上執行，需要把記憶體調至4g，否則報錯）

&nbsp;

### 4.啟動VN Trader
在資料夾tests\trader中找到run.py檔案。右鍵進入終端，輸入下面命令即可啟動VN Trader。
```
python run.py 
```
