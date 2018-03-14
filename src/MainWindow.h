#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<TWindow.h>
#include<TPictureBox.h>
#include<TImageButton.h>
#include<memory>
#include<TAudio.h>

class MainWindow : public TSDK::TWindow
{
protected:
    void handlemessage(TSDK::TGuiMessage * msg);
private:
    const char * getNumImg(int i);
private:
    std::unique_ptr<TSDK::TPictureBox2D> m_background;
    void initializeBackground();
private:
    std::unique_ptr<TSDK::TImageButton> m_startButton,m_stopButton;
    void initializeStartButton();
    void initializeStopButton();
private:
    std::unique_ptr<TSDK::TAudioPlayer> m_startAudio,m_stopAudio;
    void initializeStartAudio();
    void initializeStopAudio();
private:
    std::unique_ptr<TSDK::TPictureBox2D> m_num1,m_num2,m_num3,m_num4;
    void initializeNum();
private:
    std::unique_ptr<std::thread> m_th;
    bool m_isRunRand=false;
public:
    void threadRandom();
private:
    bool m_isProgramRun=true;
public:
    MainWindow();
    virtual ~MainWindow();
public:
    void startButtonClick();
    void stopButtonClick();
};

#endif // MAINWINDOW_H
