#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class QTableWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //定义内存控制块 MCB
    typedef struct MCB{
        int id;             //ID
        int original_size;  //原始空间大小
        int rest_size;      //剩余空间大小
        int head_address;   //首地址
        QString work;       //分配的作业
    }MCB;

    //定义作业控制块 JCB
    typedef struct JCB{
        int id;             //ID
        int job_size;       //作业大小
        QString job_map;    //对应区块
        QString state;      //状态
    }JCB;

    QVector<MCB> memory, memory_backup; //QVector容器，_backup为记录
    QVector<JCB> jobs, job_backup;

    void getbothTable();    //取表格数据到数组
    void setbothTable();    //数组数据显示到表格

    void Head_Stablesort(QVector<MCB> *vector); //对 QVector<MCB> 按 首地址 进行 升序排序
    void Res_Ascstablesort(QVector<MCB> *vector); //对 QVector<MCB> 按 剩余空间大小 进行 升序排序
    void Res_Descstablesort(QVector<MCB> *vector); //对 QVector<MCB> 按 剩余空间大小 进行 升序排序

    void FF();
    void NF();
    void BF();
    void WF();

    void createStoragePage();   //定义创建存储管理页面函数

    QWidget *storagePage;   //1

    QGroupBox *operationsGroupBox;
    QPushButton *initButton;                //初始化按钮
    QPushButton *undoButton;                //撤销按钮
    QPushButton *runButton;   //运行按钮
    QPushButton *randMemoryButton;          //随机生成分区按钮
    QPushButton *randJobButton;             //随机生成作业按钮
    QPushButton *clearButton;               //清空按钮

    QGroupBox *freepartitionGroupBox;
    QTableWidget *partitionTable;   //分区表

    QGroupBox *arithmeticGroupBox;

    QRadioButton *FFButton;  //首次适应算法单选按钮
    QRadioButton *NFButton;  //循环首次适应算法单选按钮
    QRadioButton *BFButton;  //最佳适应算法单选按钮
    QRadioButton *WFButton;  //最坏适应算法单选按钮

    QGroupBox *jobGroupBox;
    QTableWidget *jobTable;     //作业表

private slots:  //槽
    void InitClick();   //初始化
    void UndoClick();   //撤销
    void RunClick();    //运行
    void MemoryClick(); //随机生成分区
    void JobClick();    //随机生成作业
    void ClearClick();  //清空
};

#endif // MAINWINDOW_H
