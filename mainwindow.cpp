/**
* @brief    存储管理实验
* @details  设计一个可变式分区分配的存储管理方案。并模拟实现分区的分配和回收过程。
*           对分区的管理法可以是下面四种算法：
*           （1）首次适应算法
*           （2）循环首次适应算法
*           （3）最佳适应算法
*           （4）最佳适应算法
* @author   3115005124_张逸扬
* @date     2017年12月31日11:01:23
*/
#include "mainwindow.h"

#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
//#include <QtAlgorithms>
#include <algorithm>

int rand1[10],rand2[10],rand3[10];  //随机数组

//主页面
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("3115005124_张逸扬_操作系统实验_存储管理"));   //设置标题
    createStoragePage();
    setCentralWidget(storagePage);
}

MainWindow::~MainWindow(){
}

//storagePage页面 布局
void MainWindow::createStoragePage(){
    storagePage = new QWidget;

    //operationsGroupBox初始化记录布局
    operationsGroupBox = new QGroupBox(tr("操作"));
    initButton = new QPushButton(tr("初始化"));
        connect(initButton, SIGNAL(clicked(bool)), this, SLOT(InitClick()));    //连接信号与槽
    undoButton = new QPushButton(tr("撤销"));
        connect(undoButton, SIGNAL(clicked(bool)), this, SLOT(UndoClick()));
    runButton = new QPushButton(tr("运行"));
        connect(runButton, SIGNAL(clicked(bool)), this, SLOT(RunClick()));
    randMemoryButton = new QPushButton(tr("随机生成空闲分区"));
        connect(randMemoryButton, SIGNAL(clicked(bool)), this, SLOT(MemoryClick()));
    randJobButton = new QPushButton(tr("随机生成作业"));
        connect(randJobButton, SIGNAL(clicked(bool)), this, SLOT(JobClick()));
    clearButton = new QPushButton(tr("清空"));
        connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(ClearClick()));
    //设不可选按钮
    undoButton->setEnabled(false);
    runButton->setEnabled(false);
    randMemoryButton->setEnabled(false);
    randJobButton->setEnabled(false);

    QGridLayout *operationsLayout = new QGridLayout;
    operationsLayout->addWidget(initButton, 0, 0);
    operationsLayout->addWidget(undoButton, 0, 1);
    operationsLayout->addWidget(runButton, 0, 2);
    operationsLayout->addWidget(randMemoryButton, 1, 0);
    operationsLayout->addWidget(randJobButton, 1, 1);
    operationsLayout->addWidget(clearButton, 1, 2);
    operationsGroupBox->setLayout(operationsLayout);


    //freepartitionGroupBox初始化及布局
    freepartitionGroupBox = new QGroupBox(tr("分区表"));

    partitionTable = new QTableWidget(10, 5);
    QStringList partitionLabels;
    partitionLabels << "ID" << "原始空间大小" << "剩余空间大小" << "首地址" << "分配的作业";
    partitionTable->setHorizontalHeaderLabels(partitionLabels);
    partitionTable->verticalHeader()->hide();
    partitionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);     //设置自适应列宽
    partitionTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);       //设置自适应行高

    QLayout *partitionLayout = new QVBoxLayout;
    partitionLayout->addWidget(partitionTable);
    freepartitionGroupBox->setLayout(partitionLayout);


    //arithmeticGroupBox_3初始化及布局
    arithmeticGroupBox = new QGroupBox(tr("选择算法"));
    FFButton = new QRadioButton(tr("首次适应算法（FF）"));
    NFButton = new QRadioButton(tr("循环首次适应算法（NF）"));
    BFButton = new QRadioButton(tr("最佳适应算法（BF）"));
    WFButton = new QRadioButton(tr("最坏适应算法（WF）"));

    QGridLayout *arithmeticLayout = new QGridLayout;
    arithmeticLayout->addWidget(FFButton);
    arithmeticLayout->addWidget(NFButton);
    arithmeticLayout->addWidget(BFButton);
    arithmeticLayout->addWidget(WFButton);
    arithmeticGroupBox->setLayout(arithmeticLayout);

    //jobGroupBox初始化及布局
    jobGroupBox = new QGroupBox(tr("作业表"));

    jobTable = new QTableWidget(10, 4);
    QStringList jobLabels;
    jobLabels << "ID" << "作业大小" << "对应区块" << "状态";
    jobTable->setHorizontalHeaderLabels(jobLabels);
    jobTable->verticalHeader()->hide();
    jobTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);     //设置自适应列宽
    jobTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);       //设置自适应行高

    QLayout *jobLayout = new QVBoxLayout;
    jobLayout->addWidget(jobTable);
    jobGroupBox->setLayout(jobLayout);

    //页面布局
    QGridLayout *pageLayout = new QGridLayout;
    pageLayout->setRowStretch(0, 1);
    pageLayout->setRowStretch(1, 5);
    pageLayout->setColumnStretch(0, 5);
    pageLayout->setColumnStretch(1, 3);
    pageLayout->addWidget(operationsGroupBox, 0, 0);
    pageLayout->addWidget(freepartitionGroupBox, 1, 0);
    pageLayout->addWidget(arithmeticGroupBox, 0, 1);
    pageLayout->addWidget(jobGroupBox, 1, 1);
    storagePage->setLayout(pageLayout);
}

//初始化按钮 响应
void MainWindow::InitClick(){
    int x=1,y=100;
    for(int i=0;i<10;i++){
        rand1[i] = rand()%(y-x+1)+x;    //原始空间大小随机数1~100
        rand2[i] = rand()%(y-x+1)+x;    //首地址随机数1~100
        rand3[i] = rand()%(y-x+1)+x;    //原始空间大小随机数1~100
    }

    for(int j=0;j<10;j++){
        partitionTable->setItem(j, 0, new QTableWidgetItem(QString::number(j+1)));
        partitionTable->setItem(j, 1, new QTableWidgetItem(QString::number(rand1[j])));
        partitionTable->setItem(j, 2, new QTableWidgetItem(QString::number(rand1[j])));
        partitionTable->setItem(j, 3, new QTableWidgetItem(QString::number(rand2[j])));
    }

    for(int j=0; j<10; j++){
        jobTable->setItem(j, 0, new QTableWidgetItem(QString::number(j+1)));
        jobTable->setItem(j, 1, new QTableWidgetItem(QString::number(rand3[j])));
        jobTable->setItem(j, 3, new QTableWidgetItem("N"));
    }
    runButton->setEnabled(true);
    randMemoryButton->setEnabled(true);
    randJobButton->setEnabled(true);
}

//撤销按钮 响应
void MainWindow::UndoClick(){
    //显示
    partitionTable->clearContents();
    jobTable->clearContents();
    for(int i=0; i<10; i++){
        partitionTable->setItem(i, 0, new QTableWidgetItem(QString::number(memory_backup[i].id)));
        partitionTable->setItem(i, 1, new QTableWidgetItem(QString::number(memory_backup[i].original_size)));
        partitionTable->setItem(i, 2, new QTableWidgetItem(QString::number(memory_backup[i].rest_size)));
        partitionTable->setItem(i, 3, new QTableWidgetItem(QString::number(memory_backup[i].head_address)));
        partitionTable->setItem(i, 4, new QTableWidgetItem(memory_backup[i].work));

        jobTable->setItem(i, 0, new QTableWidgetItem(QString::number(job_backup[i].id)));
        jobTable->setItem(i, 1, new QTableWidgetItem(QString::number(job_backup[i].job_size)));
        jobTable->setItem(i, 2, new QTableWidgetItem(job_backup[i].job_map));
        jobTable->setItem(i, 3, new QTableWidgetItem(job_backup[i].state));
    }
    memory.clear();
    jobs.clear();
    memory_backup.clear();
    job_backup.clear();
    runButton->setEnabled(true);
    undoButton->setEnabled(false);
}

//运行按钮 响应
void MainWindow::RunClick(){
    runButton->setEnabled(false);
    undoButton->setEnabled(true);
    if(FFButton->isChecked()){  //首次适应算法
        getbothTable();
        FF();
        setbothTable();
    } else if (NFButton->isChecked()){  //循环首次适应算法
        getbothTable();
        NF();
        setbothTable();
    } else if (BFButton->isChecked()){  //最佳适应算法
        getbothTable();
        BF();
        setbothTable();
    } else if (WFButton->isChecked()){  //最坏适应算法
        getbothTable();
        WF();
        setbothTable();
    } else {    //若没有选择算法
        QMessageBox::information(NULL, "提示", "请选择算法");
        runButton->setEnabled(true);
        undoButton->setEnabled(false);
    }
}

//随机生成空闲分区按钮 响应
void MainWindow::MemoryClick(){
    int x=1,y=100;
    for(int i=0;i<10;i++){
        rand1[i] = rand()%(y-x+1)+x;    //原始空间大小随机数1~100
        rand2[i] = rand()%(y-x+1)+x;    //首地址随机数1~100
    }

    for(int j=0;j<10;j++){
        partitionTable->setItem(j, 0, new QTableWidgetItem(QString::number(j+1)));
        partitionTable->setItem(j, 1, new QTableWidgetItem(QString::number(rand1[j])));
        partitionTable->setItem(j, 2, new QTableWidgetItem(QString::number(rand1[j])));
        partitionTable->setItem(j, 3, new QTableWidgetItem(QString::number(rand2[j])));
    }
}

//随机生成作业按钮 响应
void MainWindow::JobClick(){
    int x=1,y=100;
    for(int i=0;i<10;i++){
        rand3[i] = rand()%(y-x+1)+x;    //原始空间大小随机数1~100
    }

    for(int j=0; j<10; j++){
        jobTable->setItem(j, 0, new QTableWidgetItem(QString::number(j+1)));
        jobTable->setItem(j, 1, new QTableWidgetItem(QString::number(rand3[j])));
        jobTable->setItem(j, 3, new QTableWidgetItem("N"));
    }
}

//清空按钮 响应
void MainWindow::ClearClick(){
    partitionTable->clearContents();
    jobTable->clearContents();
    memory.clear();
    jobs.clear();
    memory_backup.clear();
    job_backup.clear();
    //设不可选按钮
    undoButton->setEnabled(false);
    runButton->setEnabled(false);
    randMemoryButton->setEnabled(false);
    randJobButton->setEnabled(false);
}

//FF算法
void MainWindow::FF(){
    //核心算法部分
    Head_Stablesort(&memory);
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            if(memory[j].rest_size >= jobs[i].job_size){
                memory[j].rest_size -= jobs[i].job_size;
                memory[j].work = memory[j].work + "|" + QString::number(jobs[i].id) + " ";
                jobs[i].job_map = QString::number(memory[j].id);
                jobs[i].state = "Y";
                break;
            }else {
                jobs[i].job_map = "未分配";
                jobs[i].state = "N";
            }
        }
    }
}

//NF算法
void MainWindow::NF(){
    //核心算法部分
    Head_Stablesort(&memory);
    int temp=0;
    for(int i=0; i<10; i++){
        for(int j=temp,sum=1; sum<10; sum++,j++){
            j=j%10;
            if(memory[j].rest_size >= jobs[i].job_size){
                memory[j].rest_size -= jobs[i].job_size;
                memory[j].work = memory[j].work + "|" + QString::number(jobs[i].id) + " ";
                jobs[i].job_map = QString::number(memory[j].id);
                jobs[i].state = "Y";
                temp =j+1;    //记录当前“指针”
                break;
            }else {
                jobs[i].job_map = "未分配";
                jobs[i].state = "N";
            }
        }
    }
}

//BF算法
void MainWindow::BF(){
    //核心算法部分
    Res_Ascstablesort(&memory);
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            if(memory[j].rest_size >= jobs[i].job_size){
                memory[j].rest_size -= jobs[i].job_size;
                memory[j].work = memory[j].work + "|" + QString::number(jobs[i].id) + " ";
                jobs[i].job_map = QString::number(memory[j].id);
                jobs[i].state = "Y";
                break;
            }else {
                jobs[i].job_map = "未分配";
                jobs[i].state = "N";
            }
            Res_Ascstablesort(&memory);
        }
    }
}

//WF算法
void MainWindow::WF(){
    //核心算法部分
    Res_Descstablesort(&memory);
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            if(memory[j].rest_size >= jobs[i].job_size){
                memory[j].rest_size -= jobs[i].job_size;
                memory[j].work = memory[j].work + "|" + QString::number(jobs[i].id) + " ";
                jobs[i].job_map = QString::number(memory[j].id);
                jobs[i].state = "Y";
                break;
            }else {
                jobs[i].job_map = "未分配";
                jobs[i].state = "N";
            }
            Res_Descstablesort(&memory);
        }
    }
}

//取两表格数据到数组
void MainWindow::getbothTable(){
    //赋值
    for(int i=0; i<10; i++){
        memory.append(MCB{
                          partitionTable->takeItem(i, 0)->text().toInt(),        //ID
                          partitionTable->takeItem(i, 1)->text().toInt(),        //原始空间大小
                          partitionTable->takeItem(i, 2)->text().toInt(),        //剩余空间大小
                          partitionTable->takeItem(i, 3)->text().toInt(),        //首地址
                          ""                                                     //分配的作业
                      });

        jobs.append(JCB{
                       jobTable->takeItem(i, 0)->text().toInt(),   //ID
                       jobTable->takeItem(i, 1)->text().toInt(),   //作业大小
                       "",                                         //对应区块
                       jobTable->takeItem(i, 3)->text()            //状态
                   });

        memory_backup=memory;
        job_backup=jobs;
    }
}

//两数组数据显示到表格
void MainWindow::setbothTable(){
    for(int i=0; i<memory.size(); i++){
        partitionTable->setItem(i, 0, new QTableWidgetItem(QString::number(memory[i].id)));
        partitionTable->setItem(i, 1, new QTableWidgetItem(QString::number(memory[i].original_size)));
        partitionTable->setItem(i, 2, new QTableWidgetItem(QString::number(memory[i].rest_size)));
        partitionTable->setItem(i, 3, new QTableWidgetItem(QString::number(memory[i].head_address)));
        partitionTable->setItem(i, 4, new QTableWidgetItem(memory[i].work));

    }
    for(int i=0; i<jobs.size(); i++){
        jobTable->setItem(i, 0, new QTableWidgetItem(QString::number(jobs[i].id)));
        jobTable->setItem(i, 1, new QTableWidgetItem(QString::number(jobs[i].job_size)));
        jobTable->setItem(i, 2, new QTableWidgetItem(jobs[i].job_map));
        jobTable->setItem(i, 3, new QTableWidgetItem(jobs[i].state));
    }
}

//对memory按 首地址 进行升序排序 使用Lambda表达式 std::stable_sort
void MainWindow::Head_Stablesort(QVector<MCB> *vector){
    std::stable_sort(vector->begin(),vector->end(),[](const MCB &A,const MCB &B){
        return A.head_address < B.head_address;});
}

//对memory按 剩余空间大小 进行升序排序 使用Lambda表达式 std::stable_sort
void MainWindow::Res_Ascstablesort(QVector<MCB> *vector){
    std::stable_sort(vector->begin(),vector->end(),[](const MCB &A,const MCB &B){
        return A.rest_size < B.rest_size;});
}

//对memory按 剩余空间大小 进行降序排序 使用Lambda表达式 std::stable_sort
void MainWindow::Res_Descstablesort(QVector<MCB> *vector){
    std::stable_sort(vector->begin(),vector->end(),[](const MCB &A,const MCB &B){
        return A.rest_size > B.rest_size;});
}
