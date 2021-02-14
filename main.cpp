#include <QApplication>
#include <QCommandLineParser>
#include <QUrl>
#include <QDir>

#include <KAboutData>
#include <KLocalizedString>
#include <KMessageBox>
#include "mainwindow.hpp"

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("texteditor");

    KAboutData aboutData(
        // Internal program name.
        QStringLiteral("texteditor"),
        // Dispplay name.
        i18n("texteditor"),
        // Program's version string.
        QStringLiteral("1.0"),
        // Short description.
        i18n("A simple KTextArea"),
        // Licence.
        KAboutLicense::GPL,
        // Copyright.
        i18n("(c) 2020"),
        // Optional text shown.
        i18n("Some text..."),
        // Program's url.
        QStringLiteral("http://example.org"),
        // Bug report email.
        QStringLiteral("bus@example.org"));

    aboutData.addAuthor(
        i18n("name"),
        i18n("Task"),
        QStringLiteral("user@example.org"),
        QStringLiteral("http://example.org"),
        QStringLiteral("OSC Username"));

    KAboutData::setApplicationData(aboutData);

    QCommandLineParser parser;

    aboutData.setupCommandLine(&parser);
    parser.addPositionalArgument(QStringLiteral("file"), i18n("Document to open"));
    parser.process(app);
    aboutData.processCommandLine(&parser);

    MainWindow *window = new MainWindow();

    window->show();

    if (parser.positionalArguments().count() > 0)
    {
        window->openFileFromUrl(QUrl::fromUserInput(parser.positionalArguments().at(0), QDir::currentPath()));
    }

    return app.exec();
}
