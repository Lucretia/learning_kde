#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <KXmlGuiWindow>

class KTextEdit;
class KJob;

class MainWindow : public KXmlGuiWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        void openFileFromUrl(const QUrl &inputFilename);

    private:
        void setupActions();
        void saveFileToDisk(const QString &outputFilename);

    private Q_SLOTS:
        void newFile();
        void openFile();
        void saveFile();
        void saveFileAs();

        void downloadFinished(KJob *job);

    private:
        KTextEdit *textArea;
        QString    filename;
};

#endif // !MAINWINDOW_HPP