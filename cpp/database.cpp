#include "database.h"
#include<QCoreApplication>
database::database(QObject *parent)
    : QObject{parent}
{
    //创建sqlite数据库
    createdatabase();

    //初始化数据库
    if(!initdatabase()){
        QString text("数据库访问或者创造出现了问题");
        throw std::runtime_error(text.toUtf8().constData());
    }
}

void database::createdatabase()
{
    QString databaseFileName = "record.db";
    QString databaseFilePath = QDir(QCoreApplication::applicationDirPath()).filePath(databaseFileName);

    QFileInfo checkFile(databaseFilePath);
    bool isExist = checkFile.exists() && checkFile.isFile();
    if (!isExist) {
        qDebug() << "Database file does not exist. It will be created upon opening.";
    }

    // 检查是否已经存在名为 "recordConnection" 的连接
    if (!QSqlDatabase::contains("recordConnection")) {
        // 获取一个 SQLite 数据库连接，并命名为 "recordConnection"
        db = QSqlDatabase::addDatabase("QSQLITE", "recordConnection");
        db.setDatabaseName(databaseFilePath);  // 设置数据库文件的完整路径

        // 尝试打开数据库连接
        if (!db.open()) {
            qDebug() << "Failed to open the database:" << db.lastError().text();
        } else {
            qDebug() << "Database opened successfully.";
        }
    } else {
        // 如果已经存在连接，则获取该连接
        db = QSqlDatabase::database("recordConnection");
    }
}

bool database::initdatabase()
{
    // 假设 db 是 QSqlDatabase 类型并且已正确初始化
    // 检查数据库文件是否存在（假设你传入文件路径）
    QString databaseFileName = "record.db";
    QString databaseFilePath = QDir(QCoreApplication::applicationDirPath()).filePath(databaseFileName);

    QFileInfo checkFile(databaseFilePath);
    bool isExist = checkFile.exists() && checkFile.isFile();
    if (!isExist) {
        qDebug() << "Database file does not exist. Error extend.";
        return false;
    }

    // 打开数据库连接
    if (!db.open()) {
        qDebug() << "Failed to open the database:" << db.lastError().text();
        QString error =QString ("Failed to open the database:%1").arg(db.lastError().text());
        throw std::runtime_error(error.toUtf8().constData());
        return false;
    }

    // 创建表格
    QSqlQuery query(db);
    bool success = query.exec("CREATE TABLE IF NOT EXISTS TextEntries ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "textContent TEXT, "
                              "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)");

    if (!success) {
        qDebug() << "Failed to create table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool database::insertTextWithTimestamp(const QString& text)
{
    // 确保数据库已经打开
    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return false;
    }

    // 创建查询对象
    QSqlQuery query(db);

    // 使用占位符来插入数据
    query.prepare("INSERT INTO TextEntries (textContent) VALUES (:textContent)");

    // 绑定参数
    query.bindValue(":textContent", text);

    // 执行查询
    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError().text();
        return false;
    }

    qDebug() << "Text inserted successfully with timestamp.";
    return true;
}
bool database::queryTextEntries()
{
    // 确保数据库已经打开
    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return false;
    }

    // 创建查询对象
    QSqlQuery query(db);

    // 执行查询，选择所有数据
    if (!query.exec("SELECT id, textContent, timestamp FROM TextEntries")) {
        qDebug() << "Query failed:" << query.lastError().text();
        return false;
    }

    // 获取查询结果
    QList<QPair<int, QString>> results;  // 用来保存查询结果
    while (query.next()) {
        int id = query.value("id").toInt();           // 获取id字段
        QString textContent = query.value("textContent").toString(); // 获取textContent字段
        QString timestamp = query.value("timestamp").toString(); // 获取timestamp字段

        // 输出每一条记录
        qDebug() << "ID:" << id << "Text:" << textContent << "Timestamp:" << timestamp;

        // 保存结果
        results.append(qMakePair(id, textContent));
    }

    // 如果没有记录
    if (results.isEmpty()) {
        qDebug() << "No entries found.";
    }

    // 返回查询成功
    return true;
}

QString database::readdata(int id)
{
    QSqlQuery query(db);
    // 使用占位符控制 LIMIT 和 OFFSET
    query.prepare("SELECT id, textContent FROM TextEntries ORDER BY id DESC LIMIT :limit OFFSET :offset");
    query.bindValue(":limit", 1);    // 只取 1 条数据
    query.bindValue(":offset", id-1);   // 跳过最新的数据（即跳过 id-1 条）
    // 执行 SELECT 语句，按 id 倒序排列，只取第一行
    if (!query.exec()) {

        qDebug() << "Error: Unable to execute query!" << query.lastError().text();
        return QString();  // 返回空字符串表示读取失败
    }

    // 如果查询有结果，则读取数据
    if (query.next()) {
        QString id = query.value(0).toString();               // 获取 id
        QString textContent = query.value(1).toString(); // 获取 textContent

        qDebug() << "Latest Data -> ID:" << id << ", Text Content:" << textContent;
        return textContent;  // 返回最新记录的文本内容
    } else {
        qDebug() << "No data found in the database.";
        return QString();  // 返回空字符串表示数据库中无数据
    }
}
