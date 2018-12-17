//
// Created by eliran on 12/17/18.
//

#ifndef FIRSTPROJECT_CONDITIONPARSER_H
#define FIRSTPROJECT_CONDITIONPARSER_H


#include "Command.h"
#include <map>
class ConditionParser : public Command {

private:
    vector<Command> vec; // אלי אמר שצריך להחזיק רשימה, אבל לא בטוח צריך כי מקבלים ב exectute

public:
    int execute(const vector<string> &parameters, int position) override;

    /*
     * הפונקציות שחשבתי עליהן שצריך לעשות:
     * כל המטרה של קונדישן פארסר, זה לבדוק האם התנאי מתקיים
     * First step: תיצור אקספרשן מהביטוי שמגיע עד הסוגר פותח הראשון
     * Second step: תבדוק האם התנאי מתקיים על ידי :
     * לגשת ל symbol table, לקחת את הערך ולפרש אותו, ובעזרת האופטרים שעשינו השוואת, לבדוק אם מתקיים
     * לדוגמא אם יש לנו while alt < 50 אחרי הפיצול שנעשה, נדע שזו לולאת while
     * לאחר מכן ניש לטבלה וניקח את הערך של alt
     * ונעשה קספרשן לשתי הצדדים, ונבדוק עם האופרטור.
     * אם התנאי מתקיים :
     * עבור כל קומאנד שנמצא עד ה סוגר סוגר, נבצע אותו, ונעדכן בטבלת הסימבול אם הערך החדש של המשתנה.
     * עבור לולאת if אותו דבר, רק שחוזרים פעם אחת במידה והתנאי מתקיים.
     */
};


#endif //FIRSTPROJECT_CONDITIONPARSER_H
