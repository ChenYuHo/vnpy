# 貢獻程式碼

---
## 建立PR
我們歡迎任何人貢獻程式碼到vn.py。  
如果希望貢獻程式碼請使用github的PR(Pull Request)的流程。

PR流程大致如下：

---
1. [建立 Issue][CreateIssue] - 對於較大的改動(如新功能，大型重構等)最好先開issue討論一下， 較小的improvement(如文件改進，bugfix等)直接發PR即可

2. Fork [vn.py][#GithubVnpy] - 點選右上角**Fork**按鈕

3. Clone你自己的fork: ```git clone https://github.com/$userid/vnpy.git```
	> 如果你的fork已經過時，需要手動[sync][GithubDocForSync]

4. 從**dev**建立你自己的branch: ```git checkout -b $my_feature_branch dev```

5. 在$my_feature_branch上修改並將修改push到你Fork之後的倉庫上

6. 建立從你的fork的$my_feature_branch分支到主專案的**dev**分支的[Pull Request]:  
 [點開這裡][CreatePR] ，再點選**compare across forks**，選擇需要的fork和branch建立PR

---

建立完PR之後請耐心等待：我們一旦有空就會檢查PR，一旦你的程式碼有用且[符合要求](#程式碼風格)，就會被合併！


---
## 程式碼風格
在為vn.py寫程式碼的時候，需要遵循一些基本的規則，否則你的程式碼可能無法被merge。
這些規則包括：
1. [命名規則](#命名規則)
2. [程式碼格式](#程式碼格式)
3. [程式碼質量檢查](#程式碼質量檢查)


### 命名規則
我們的程式碼的命名規則如下：

* 類屬性、類方法、引數和變數使用小寫加下劃線的形式
* 類名使用駝峰式命名
* 常量使用大寫加下劃線的形式

例如：
```python
DEFAULT_PATH = "/tmp/vn.py/"
class ClassA:
    def __init__(self, arg_one: int, arg_two: str):
        if arg_two is None:
            arg_two = DEFAULT_PATH
        self.property_one = arg_one
        variable_one = "some string"
```


### 程式碼格式
我們對程式碼格式沒有特別嚴格的要求，但是至少要符合pep8標準，並且額外要在類和所有函式下面帶上docstring(就是一段"""""")。

要讓程式碼符合pep8標準，寫完程式碼之後使用[autopep8](https://github.com/hhatto/autopep8)格式化你的程式碼就可以了:  
```bash
autopep8 --in-place --recursive . 
```

### 程式碼質量檢查
使用[flake8](https://pypi.org/project/flake8/)檢查你的程式碼，確保沒有error和warning。
在專案根目錄下執行```flake8```就可以檢查出程式碼中書寫不嚴謹的地方了。如果檢查出error或者warning，說明你的程式碼需要進行一些修改以提升質量。

[GithubVnpy]:https://github.com/vnpy/vnpy
[GithubDocForSync]:https://help.github.com/articles/syncing-a-fork/
[CreateIssue]:https://github.com/vnpy/vnpy/issues/new
[CreatePR]:https://github.com/vnpy/vnpy/compare?expand=1

