#include <QApplication>
#include <QCommandLineParser>
#include <KAboutData>
#include <KLocalizedString>
#include <KMessageBox>
#include "mainwindow.hpp"

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("mainwindow");

    KAboutData aboutData(
        // Internal program name.
        QStringLiteral("mainwindow"),
        // Dispplay name.
        i18n("mainwindow"),
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
    parser.process(app);
    aboutData.processCommandLine(&parser);

    MainWindow *window = new MainWindow();

    window->show();

    return app.exec();
}
