#include "MainWindow.h"
#include<thread>
#include<random>

void MainWindow::handlemessage(TSDK::TGuiMessage * msg)
{
    if(this->m_isRunRand)
    {
        unsigned int num=atoi(msg->value(0).c_str());
        this->m_num4->loadImageFromFile(this->getNumImg(num%10));
        num/=10;
        this->m_num3->loadImageFromFile(this->getNumImg(num%10));
        num/=10;
        this->m_num2->loadImageFromFile(this->getNumImg(num%10));
        num/=10;
        this->m_num1->loadImageFromFile(this->getNumImg(num%10));
    }
}

const char * MainWindow::getNumImg(int i)
{
    switch(i)
    {
    case 0:return "Images/number0.png";
    case 1:return "Images/number1.png";
    case 2:return "Images/number2.png";
    case 3:return "Images/number3.png";
    case 4:return "Images/number4.png";
    case 5:return "Images/number5.png";
    case 6:return "Images/number6.png";
    case 7:return "Images/number7.png";
    case 8:return "Images/number8.png";
    case 9:return "Images/number9.png";
    default:return "";
    }
}

void MainWindow::initializeBackground()
{
    this->m_background.reset(new TSDK::TPictureBox2D("Images/background.jpg",this));
    this->m_background->scaled(10,10);
    this->m_background->show();
}

void MainWindow::initializeStartButton()
{
    this->m_startButton.reset(new TSDK::TImageButton("Images/startButton.jpg",this));
    this->m_startButton->move(-0.005f,-0.4f);
    this->m_startButton->scaled(3.0f,1.2f);
    this->m_startButton->setOnClicked(std::bind(&MainWindow::startButtonClick,this));
    this->m_startButton->show();
}

void MainWindow::initializeStopButton()
{
    this->m_stopButton.reset(new TSDK::TImageButton("Images/stopButton.jpg",this));
    this->m_stopButton->move(-0.005f,-0.7f);
    this->m_stopButton->scaled(2.0f,0.8f);
    this->m_stopButton->setOnClicked(std::bind(&MainWindow::stopButtonClick,this));
    this->m_stopButton->show();
}

void MainWindow::initializeStartAudio()
{
    this->m_startAudio.reset(new TSDK::TOpenALPlayer());
    this->m_startAudio->openFromFile("Audio/001.wav",true);
}

void MainWindow::initializeStopAudio()
{
    this->m_stopAudio.reset(new TSDK::TOpenALPlayer());
    this->m_stopAudio->openFromFile("Audio/002.wav");
}

void MainWindow::initializeNum()
{
    this->m_num2.reset(new TSDK::TPictureBox2D(this));
    this->m_num2->loadImageFromFile(this->getNumImg(0));
    this->m_num2->move(-0.11f,0.0f);
    this->m_num2->scaled(0.8f,2.4f);
    this->m_num2->show();

    this->m_num3.reset(new TSDK::TPictureBox2D(this));
    this->m_num3->loadImageFromFile(this->getNumImg(0));
    this->m_num3->move(0.09f,0.0f);
    this->m_num3->scaled(0.8f,2.4f);
    this->m_num3->show();

    this->m_num4.reset(new TSDK::TPictureBox2D(this));
    this->m_num4->loadImageFromFile(this->getNumImg(0));
    this->m_num4->move(0.27f,0.0f);
    this->m_num4->scaled(0.8f,2.4f);
    this->m_num4->show();

    this->m_num1.reset(new TSDK::TPictureBox2D(this));
    this->m_num1->loadImageFromFile(this->getNumImg(0));
    this->m_num1->move(-0.29f,0.0f);
    this->m_num1->scaled(0.8f,2.4f);
    this->m_num1->show();
}

MainWindow::MainWindow()
    :TWindow(TWindow::GameWindow_Mode)
{
    this->setWindowTitle("计算机协会抽奖系统");
    this->initializeBackground();
    this->initializeStartButton();
    this->initializeStopButton();
    this->initializeNum();

    this->initializeStartAudio();
    this->initializeStopAudio();

    this->m_th.reset(new std::thread(std::bind(&MainWindow::threadRandom,this)));
    this->m_th->detach();
}

MainWindow::~MainWindow()
{
    this->m_isProgramRun=false;
}

void MainWindow::startButtonClick()
{
    this->m_stopAudio->stop();
    if(this->m_startAudio->state()!=TSDK::TAudioPlayer::Playing)
        this->m_startAudio->play();

    this->m_isRunRand=true;
}

void MainWindow::stopButtonClick()
{
    if(this->m_startAudio->state()==TSDK::TAudioPlayer::Playing)
    {
        this->m_startAudio->stop();
        this->m_stopAudio->play();
    }

    this->m_isRunRand=false;
}

void MainWindow::threadRandom()
{
    std::default_random_engine random;
    std::uniform_int_distribution<unsigned int> range(1,9999);

    std::chrono::milliseconds sec(300);

    while(this->m_isProgramRun)
    {
        if(this->m_isRunRand)
        {
            TSDK::TGuiMessage msg(0,1);
            msg.setValue(std::to_string(range(random)),0);
            this->sendMessage(&msg);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        else
            std::this_thread::sleep_for(sec);
    }
}
