#pragma once

#include <QString>
#include <QStringList>
#include <vector>
#include <QDebug>

struct Version{
    int major,minor,patch;
    Version(int major=0,int minor=0,int patch=0):
        major(major),minor(minor),patch(patch){}
    QString toString() const {
        return QString("%1.%2.%3").arg(major).arg(minor).arg(patch);
    }
    static Version fromString(QString str){
        if(str.isEmpty()) return Version();
        if(str[0]=='v') str.remove(0,1);
        QStringList listStr=str.split(".");
        std::vector<int> listInt;
        bool ok=true;
        for(auto it=listStr.begin();it!=listStr.end();it++){
            int x=it->toInt(&ok);
            if(!ok) break;
            listInt.push_back(x);
        }
        if(!ok) return Version();
        Version ver;
        ver.major=listInt[0];
        if(listInt.size()>1) ver.minor=listInt[1];
        if(listInt.size()>2) ver.patch=listInt[2];
        return ver;
    }
    bool operator<(const Version& v) const{
        if(major!=v.major) return (major<v.major);
        if(minor!=v.minor) return (minor<v.minor);
        if(patch!=v.patch) return (patch<v.patch);
        return false;
    }
};

extern const Version version;
