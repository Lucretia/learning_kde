#include <QApplication>
#include <QCommandLineParser>
#include <KAboutData>
#include <KLocalizedString>
#include <KMessageBox>

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("tutorials");

    KAboutData aboutData(
        // Internal program name.
        QStringLiteral("tutorial1"),
        // Dispplay name.
        i18n("Tutorial 1"),
        // Program's version string.
        QStringLiteral("1.0"),
        // Short description.
        i18n("Displays a KMessageBox popup"),
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

    KGuiItem yesButton(i18n("Hello"), QString(),
        i18n("This is a tooltip"),
        i18n("This is a WhatsThis help text."));

    KGuiItem noButton(i18n("Deny"), QString(),
        i18n("Deny tooltip"),
        i18n("Deny WhatsThis help text."));

    return KMessageBox::questionYesNo(nullptr,
        i18n("Hello, world!"),
        i18n("Hello"),
        yesButton, noButton) == KMessageBox::Yes ? EXIT_SUCCESS : EXIT_FAILURE;
}
