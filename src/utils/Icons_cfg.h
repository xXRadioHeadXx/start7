#ifndef ICONS_CFG_H
#define ICONS_CFG_H

#include <QPixmap>


class Icons_cfg
{
public:
    Icons_cfg();

    static QPixmap sd();
    static QPixmap sd_basalt();
    static QPixmap sd_connect_block();
    static QPixmap iu();
    static QPixmap BOD_T4K_M();
    static QPixmap Y4_T4K_M();
    static QPixmap TG();
    static QPixmap RLM_KRL();
    static QPixmap Y4_SOTA();
    static QPixmap DD_SOTA();
    static QPixmap KL();
    static QPixmap NET_DEV();
    static QPixmap ONVIF();
    static QPixmap INFO_TABLO();   
    static QPixmap default_square_gray();

    static QPixmap empty();
    static QPixmap DK();
    static QPixmap Alarm();

    //         Y4_SOTA = 30,//Участок Сота
    //         DD_SOTA = 28,//ДД Сота
};

#endif // ICONS_CFG_H
