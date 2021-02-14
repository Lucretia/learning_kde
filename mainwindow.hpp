#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <KXmlGuiWindow>

class KTextEdit;

class MainWindow : public KXmlGuiWindow
{
    public:
        explicit MainWindow(QWidget *parent = nullptr);

    private:
        KTextEdit *textArea;

        void setupActions();
};

#endif // !MAINWINDOW_HPP