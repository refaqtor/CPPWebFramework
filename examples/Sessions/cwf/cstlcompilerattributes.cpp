/**
  @file cstlcompilerattributes.cpp
  @author Herik Lima
*/

#include "cstlcompilerattributes.h"
#include <QVariant>
#include <cwf/metaclassparser.h>

namespace CWF
{
    CSTLCompilerAttributes::CSTLCompilerAttributes(QMap<QString, QObject *> &objects) : objects(objects)
    {
    }

    QString CSTLCompilerAttributes::buildAttributes(QMap<QString, QString> &attr, bool keyValue)
    {
        QString htmlOut;
        for(QMap<QString, QString>::iterator it = attr.begin(); it != attr.end(); ++it)
        {
            compileAttributes(attr);
            if(keyValue)
                htmlOut += " " + it.key() + "=\"" + it.value() + "\"";
            else
                htmlOut += it.value();
        }
        return htmlOut;
    }

    void CSTLCompilerAttributes::compileAttributes(QMap<QString, QString> &attr)
    {
        for(QMap<QString, QString>::iterator it = attr.begin(); it != attr.end(); ++it)
        {
            QString outPutText;
            QString &value = it.value();
            compile(value, outPutText);
            value = outPutText;
            /*
            //Compile at runtime
            if(value.startsWith("#{") && value.endsWith("}"))
            {
                value.replace("#{", "").replace("}", "");
                Properties prop(value);
                if(!objects.contains(prop.m_class))
                {
                    value = "***ERROR - OBJECT " + prop.m_class + " DOES NOT EXIST.***";
                }
                else
                {
                    QObject *object = objects[prop.m_class];
                    bool ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(QString, value));
                    if(!ok)
                    {
                        value = "***ERROR - METHOD " + prop.m_method + " .***";
                    }
                }
            }
            */
        }
    }

    void CSTLCompilerAttributes::compile(QString &text, QString &outPutText)
    {
        bool start = false;
        int size = text.size();
        QString expr;

        for(int i = 0; i < size; ++i)
        {
            QChar ch = text[i];
            if(ch == '#')
            {
                if((i + 1) < size)
                {
                    QChar c = text[i + 1];
                    if(c == '{')
                    {
                        start = true;
                    }
                }
            }
            else if(ch == '}')
            {
                if(start)
                {
                    start = false;
                    expr.replace("#{", "");
                    Properties prop(expr);
                    if(!objects.contains(prop.m_class))
                    {
                        outPutText += "***ERROR - OBJECT " + prop.m_class + " DOES NOT EXIST.***";
                    }
                    else
                    {
                        QString value;
                        QObject *object = objects[prop.m_class];
                        bool ok = false;
                        MetaClassParser metaClassParser(object);
                        QString methodReturnType(std::move(metaClassParser.getReturnType(prop.m_method + "()")));

                        if(!methodReturnType.isEmpty())
                        {
                            if(methodReturnType == "QString")
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(QString, value));
                            else if(methodReturnType == "std::string")
                            {
                                std::string returnValue;
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(std::string, returnValue));
                                value = returnValue.data();
                            }
                            else if(methodReturnType == "bool")
                            {
                                bool returnValue;
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(bool, returnValue));
                                value = std::move(QString::number(returnValue));
                            }
                            else if(methodReturnType == "char")
                            {
                                char returnValue;
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(char, returnValue));
                                value.push_back(returnValue);
                            }
                            else if(methodReturnType == "unsigned char")
                            {
                                unsigned char returnValue;
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(unsigned char, returnValue));
                                value.push_back(returnValue);
                            }
                            else if(methodReturnType == "char*")
                            {
                                char *returnValue;
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(char *, returnValue));
                                value.push_back(returnValue);
                            }
                            else if(methodReturnType == "unsigned char*")
                            {
                                unsigned char *returnValue;
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(unsigned char *, returnValue));
                                value = *returnValue;
                            }
                            else if(methodReturnType == "short")
                            {
                                short returnValue;
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(short, returnValue));
                                value = std::move(QString::number(returnValue));
                            }
                            else if(methodReturnType == "unsigned short")
                            {
                                unsigned short returnValue;
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(unsigned short, returnValue));
                                value = std::move(QString::number(returnValue));
                            }
                            else if(methodReturnType == "int")
                            {
                                int returnValue;
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(int, returnValue));
                                value = std::move(QString::number(returnValue));
                            }
                            else if(methodReturnType == "unsigned int")
                            {
                                unsigned int returnValue;
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(unsigned int, returnValue));
                                value = std::move(QString::number(returnValue));
                            }
                            else if(methodReturnType == "long")
                            {
                                long returnValue;
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(long, returnValue));
                                value = std::move(QString::number(returnValue));
                            }
                            else if(methodReturnType == "unsigned long")
                            {
                                unsigned long returnValue;
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(unsigned long, returnValue));
                                value = std::move(QString::number(returnValue));
                            }
                            else if(methodReturnType == "long long")
                            {
                                long long returnValue;
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(long long, returnValue));
                                value = std::move(QString::number(returnValue));
                            }
                            else if(methodReturnType == "unsigned long long")
                            {
                                unsigned long long returnValue;
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(unsigned long long, returnValue));
                                value = std::move(QString::number(returnValue));
                            }
                            else if(methodReturnType == "float")
                            {
                                float returnValue;
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(float, returnValue));
                                value = std::move(QString::number(returnValue));
                            }
                            else if(methodReturnType == "double")
                            {
                                double returnValue;
                                ok = QMetaObject::invokeMethod(object, prop.m_method.toStdString().data(), Qt::DirectConnection, Q_RETURN_ARG(double, returnValue));
                                value = std::move(QString::number(returnValue));
                            }

                            if(!ok)
                            {
                                outPutText += "***ERROR - METHOD " + prop.m_method + " .***";
                            }
                            else
                            {
                                outPutText += value;
                            }
                        }
                        else
                        {
                            outPutText += "***ERROR - METHOD NOT FOUND " + prop.m_method + " .***";
                        }
                    }
                    expr.clear();
                    continue;
                }
            }
            if(start)
            {
                expr.push_back(ch);
            }
            else
            {
                outPutText.push_back(ch);
            }
        }
    }

    QMap<QString, QString> CSTLCompilerAttributes::getAttributes(const QXmlStreamAttributes &attributes)
    {
        QMap<QString, QString> attr;
        for(int i = 0; i < attributes.size(); ++i)
        {
            QString name(std::move(attributes[i].name().toString()));
            QString value(std::move(attributes[i].value().toString()));
            attr.insert(name, value);
        }
        return attr;
    }
}
