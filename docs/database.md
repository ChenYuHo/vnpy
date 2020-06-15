# 資料庫配置

VN Trader目前支援以下四種資料庫：  

 * [SQLite](#sqlite)（預設）
 * [MySQL](#sqlmysqlpostgresql)
 * [PostgreSQL](#sqlmysqlpostgresql)
 * [MongoDB](#mongodb)
 
如果需要配置資料庫，請點選配置。然後按照各個資料庫所需的欄位填入相對應的值即可。

---
## SQLite
需要填寫以下欄位：

| 欄位名            | 值 |
|---------           |---- |
|database.driver     | sqlite |
|database.database   | 資料庫檔案（相對於trader目錄） |
 
SQLite的例子：

| 欄位名            | 值 |
|---------           |---- |
|database.driver     | sqlite |
|database.database   | database.db |


---
## SQL(MySQL,PostgreSQL)

需要填寫以下欄位：

| 欄位名            | 值 |
|---------           |---- |
|database.driver     | "mysql"或"postgresql" |
|database.host       | 地址 |
|database.port       | 埠 |
|database.database   | 資料庫名 |
|database.user       | 使用者名稱 |
|database.password   | 密碼 |
 
MySQL的例子：

| 欄位名            | 值 |
|---------           |----  |
|database.driver     | mysql |
|database.host       | localhost |
|database.port       | 3306 |
|database.database   | vnpy |
|database.user       | root |
|database.password   | .... |

> vnpy不會主動為關係型資料庫建立資料庫，所以請確保你所填的database.database欄位對應的資料庫已經建立好了  
> 若未建立資料庫，請手動連上資料庫並執行該命令：```create database <你填的database.database>;```   

---
## MongoDB

需要填寫以下欄位：

| 欄位名            | 值 |          是否必填|
|---------           |---- |  ---|
|database.driver     | "mysql"或"postgresql" | 必填 |
|database.host       | 地址| 必填 |
|database.port       | 埠| 必填 |
|database.database   | 資料庫名| 必填 |
|database.user       | 使用者名稱| 可選 |
|database.password   | 密碼| 可選 |
|database.authentication_source   | [建立使用者所用的資料庫][AuthSource]| 可選 |
 
MongoDB的帶認證例子：

| 欄位名            | 值 |
|---------           |----  |
|database.driver     | mongodb |
|database.host       | localhost |
|database.port       | 27017 |
|database.database   | vnpy |
|database.user       | root |
|database.password   | .... |
|database.authentication_source   | vnpy |


[AuthSource]: https://docs.mongodb.com/manual/core/security-users/#user-authentication-database