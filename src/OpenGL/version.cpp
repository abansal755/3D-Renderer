#include "version.h"

QOpenGLFunctions_3_3_Core* gl(){
    return QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
}
