#pragma once

#include <QString>

struct Version{
    int major,minor,patch;
    Version(int major,int minor,int patch):
        major(major),minor(minor),patch(patch){}
    QString toString() const {
        return QString("%1.%2.%3").arg(major).arg(minor).arg(patch);
    }
};

extern const Version version;
