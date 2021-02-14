#include <QApplication>
#include <QAction>
#include <QSaveFile>
#include <QFileDialog>
#include <QTextStream>
#include <QByteArray>

#include <KTextEdit>
#include <KLocalizedString>
#include <KActionCollection>
#include <KStandardAction>
#include <KMessageBox>
#include <KIO/Job>

#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent), filename(QString())
{
    textArea = new KTextEdit();

    setCentralWidget(textArea);
    setupActions();
}

void MainWindow::openFileFromUrl(const QUrl &inputFilename)
{
    if (!inputFilename.isEmpty())
    {
        KIO::Job *job = KIO::storedGet(inputFilename);

        filename = inputFilename.toLocalFile();

        connect(job, &KIO::Job::result, this, &MainWindow::downloadFinished);

        job->exec();
    }
}

void MainWindow::setupActions()
{
    QAction *clearAction = new QAction(this);

    clearAction->setText(i18n("&Clear"));
    clearAction->setIcon(QIcon::fromTheme("document-new"));

    actionCollection()->setDefaultShortcut(clearAction, Qt::CTRL + Qt::Key_W);
    actionCollection()->addAction("clear", clearAction);

    connect(clearAction, &QAction::triggered, textArea, &KTextEdit::clear);

    KStandardAction::quit(qApp, &QCoreApplication::quit, actionCollection());
    KStandardAction::open(this, &MainWindow::openFile, actionCollection());
    KStandardAction::save(this, &MainWindow::saveFile, actionCollection());
    KStandardAction::saveAs(this, &MainWindow::saveFileAs, actionCollection());
    KStandardAction::openNew(this, &MainWindow::newFile, actionCollection());

    setupGUI(Default, "texteditorui.rc");
}

void MainWindow::saveFileToDisk(const QString &outputFilename)
{
    if (!outputFilename.isNull())
    {
        QSaveFile file(outputFilename);

        file.open(QIODevice::WriteOnly);

        QByteArray outputByteArray;

        outputByteArray.append(textArea->toPlainText().toUtf8());

        file.write(outputByteArray);
        file.commit();

        filename = outputFilename;
    }
}

void MainWindow::newFile()
{
    filename.clear();
    textArea->clear();
}

void MainWindow::openFile()
{
    const QUrl filenameFromDialog = QFileDialog::getOpenFileUrl(this, i18n("Open File"));

    if (!filenameFromDialog.isEmpty())
    {
        KIO::Job *job = KIO::storedGet(filenameFromDialog);

        filename = filenameFromDialog.toLocalFile();

        connect(job, &KJob::result, this, &MainWindow::downloadFinished);

        job->exec();
    }
}

void MainWindow::saveFile()
{
    if (!filename.isEmpty())
    {
        saveFileToDisk(filename);
    }
    else
    {
        saveFileAs();
    }
}

void MainWindow::saveFileAs()
{
    saveFileToDisk(QFileDialog::getSaveFileName(this, i18n("Save File As")));
}

void MainWindow::downloadFinished(KJob *job)
{
    if (job->error())
    {
        KMessageBox::error(this, job->errorString());

        filename.clear();

        return;
    }

    const KIO::StoredTransferJob *storedJob = qobject_cast<KIO::StoredTransferJob *>(job);

    if (storedJob)
    {
        textArea->setPlainText(QTextStream(storedJob->data(), QIODevice::ReadOnly).readAll());
    }
}
