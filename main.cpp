#include <QApplication>
#include <QDebug>
#include <QLoggingCategory>
#include <QTranslator>
#include <qblewindow.h>

int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules(QStringLiteral("qt.*.debug=true"));
    QLoggingCategory::setFilterRules(QStringLiteral("qt.canbus*.debug=true"));
    QLoggingCategory::setFilterRules(QStringLiteral("qt.modbus*.debug=true"));
    QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth.debug=true"));
    QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth.bluez.debug=true"));

#ifndef Q_OS_MACOS
    /* runtime */
    setenv("QTWEBENGINE_DISABLE_SANDBOX", "1", 0);
    setenv("QT_QPA_GENERIC_PLUGINS", "Evdevtouch:Evdevmouse:Evdevkeyboard", 0);
    /* rotate QPA EGLFS panel display and touch screen */
    setenv("QT_QPA_EGLFS_ROTATION", "-90", 0);
    setenv("QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS", ":invertx=1:inverty=1:rotate=270", 0);
    /* display options */
    setenv("QT_QPA_EGLFS_PHYSICAL_WIDTH", "230", 0);
    setenv("QT_QPA_EGLFS_PHYSICAL_HEIGHT", "148", 0);
    setenv("QT_AUTO_SCREEN_SCALE_FACTOR", "0", 0);
    setenv("QT_SCALE_FACTOR_ROUNDING_POLICY", "2", 0);
    setenv("QT_ENABLE_HIGHDPI_SCALING", "1", 0);
    setenv("QT_SCREEN_SCALE_FACTORS", "1.0", 0);
    setenv("QT_QPA_FB_DRM", "1", 0);
    /* style */
    setenv("QT_QPA_PLATFORMTHEME", "qt5ct", 0);
#endif

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale: uiLanguages) {
        const QString baseName = "qble_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QBleWindow w;
    w.show();

    return a.exec();
}
