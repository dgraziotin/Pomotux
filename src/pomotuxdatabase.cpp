#include "pomotuxdatabase.hpp"
namespace pomotuxdatabase {
using namespace litesql;
ActivityInAIS::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : activityInventorySheet(ActivityInAIS::ActivityInventorySheet), activity(ActivityInAIS::Activity) {
    switch(rec.size()) {
    case 2:
        activityInventorySheet = rec[1];
    case 1:
        activity = rec[0];
    }
}
const std::string ActivityInAIS::table__("_06044cc54d2aba326c362937595d5709");
const litesql::FieldType ActivityInAIS::Activity("Activity1","INTEGER",table__);
const litesql::FieldType ActivityInAIS::ActivityInventorySheet("ActivityInventorySheet2","INTEGER",table__);
void ActivityInAIS::link(const litesql::Database& db, const pomotuxdatabase::Activity& o0, const pomotuxdatabase::ActivityInventorySheet& o1) {
    Record values;
    Split fields;
    fields.push_back(Activity.name());
    values.push_back(o0.id);
    fields.push_back(ActivityInventorySheet.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void ActivityInAIS::unlink(const litesql::Database& db, const pomotuxdatabase::Activity& o0, const pomotuxdatabase::ActivityInventorySheet& o1) {
    db.delete_(table__, (Activity == o0.id && ActivityInventorySheet == o1.id));
}
void ActivityInAIS::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<ActivityInAIS::Row> ActivityInAIS::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Activity.fullName());
    sel.result(ActivityInventorySheet.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<ActivityInAIS::Row>(db, sel);
}
template <> litesql::DataSource<pomotuxdatabase::Activity> ActivityInAIS::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Activity.fullName());
    sel.where(srcExpr);
    return DataSource<pomotuxdatabase::Activity>(db, pomotuxdatabase::Activity::Id.in(sel) && expr);
}
template <> litesql::DataSource<pomotuxdatabase::ActivityInventorySheet> ActivityInAIS::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(ActivityInventorySheet.fullName());
    sel.where(srcExpr);
    return DataSource<pomotuxdatabase::ActivityInventorySheet>(db, pomotuxdatabase::ActivityInventorySheet::Id.in(sel) && expr);
}
ActivityInTTS::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : todoTodaySheet(ActivityInTTS::TodoTodaySheet), activity(ActivityInTTS::Activity) {
    switch(rec.size()) {
    case 2:
        todoTodaySheet = rec[1];
    case 1:
        activity = rec[0];
    }
}
const std::string ActivityInTTS::table__("Activity_TodoTodaySheet_");
const litesql::FieldType ActivityInTTS::Activity("Activity1","INTEGER",table__);
const litesql::FieldType ActivityInTTS::TodoTodaySheet("TodoTodaySheet2","INTEGER",table__);
void ActivityInTTS::link(const litesql::Database& db, const pomotuxdatabase::Activity& o0, const pomotuxdatabase::TodoTodaySheet& o1) {
    Record values;
    Split fields;
    fields.push_back(Activity.name());
    values.push_back(o0.id);
    fields.push_back(TodoTodaySheet.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void ActivityInTTS::unlink(const litesql::Database& db, const pomotuxdatabase::Activity& o0, const pomotuxdatabase::TodoTodaySheet& o1) {
    db.delete_(table__, (Activity == o0.id && TodoTodaySheet == o1.id));
}
void ActivityInTTS::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<ActivityInTTS::Row> ActivityInTTS::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Activity.fullName());
    sel.result(TodoTodaySheet.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<ActivityInTTS::Row>(db, sel);
}
template <> litesql::DataSource<pomotuxdatabase::Activity> ActivityInTTS::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Activity.fullName());
    sel.where(srcExpr);
    return DataSource<pomotuxdatabase::Activity>(db, pomotuxdatabase::Activity::Id.in(sel) && expr);
}
template <> litesql::DataSource<pomotuxdatabase::TodoTodaySheet> ActivityInTTS::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(TodoTodaySheet.fullName());
    sel.where(srcExpr);
    return DataSource<pomotuxdatabase::TodoTodaySheet>(db, pomotuxdatabase::TodoTodaySheet::Id.in(sel) && expr);
}
const litesql::FieldType Activity::Own::Id("id_","INTEGER","Activity_");
const std::string Activity::type__("Activity");
const std::string Activity::table__("Activity_");
const std::string Activity::sequence__("Activity_seq");
const litesql::FieldType Activity::Id("id_","INTEGER",table__);
const litesql::FieldType Activity::Type("type_","TEXT",table__);
const litesql::FieldType Activity::MDescription("mDescription_","TEXT",table__);
const litesql::FieldType Activity::MInsertionDate("mInsertionDate_","INTEGER",table__);
const litesql::FieldType Activity::MDeadline("mDeadline_","INTEGER",table__);
const litesql::FieldType Activity::MNumPomodoro("mNumPomodoro_","INTEGER",table__);
const litesql::FieldType Activity::MOrder("mOrder_","INTEGER",table__);
const litesql::FieldType Activity::MIsFinished("mIsFinished_","INTEGER",table__);
void Activity::defaults() {
    id = 0;
    mInsertionDate = 0;
    mDeadline = 0;
    mNumPomodoro = 0;
    mOrder = 0;
    mIsFinished = false;
}
Activity::Activity(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), mDescription(MDescription), mInsertionDate(MInsertionDate), mDeadline(MDeadline), mNumPomodoro(MNumPomodoro), mOrder(MOrder), mIsFinished(MIsFinished) {
    defaults();
}
Activity::Activity(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), mDescription(MDescription), mInsertionDate(MInsertionDate), mDeadline(MDeadline), mNumPomodoro(MNumPomodoro), mOrder(MOrder), mIsFinished(MIsFinished) {
    defaults();
    size_t size = (rec.size() > 8) ? 8 : rec.size();
    switch(size) {
    case 8: mIsFinished = convert<const std::string&, bool>(rec[7]);
        mIsFinished.setModified(false);
    case 7: mOrder = convert<const std::string&, int>(rec[6]);
        mOrder.setModified(false);
    case 6: mNumPomodoro = convert<const std::string&, int>(rec[5]);
        mNumPomodoro.setModified(false);
    case 5: mDeadline = convert<const std::string&, litesql::Date>(rec[4]);
        mDeadline.setModified(false);
    case 4: mInsertionDate = convert<const std::string&, litesql::Date>(rec[3]);
        mInsertionDate.setModified(false);
    case 3: mDescription = convert<const std::string&, std::string>(rec[2]);
        mDescription.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Activity::Activity(const Activity& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), mDescription(obj.mDescription), mInsertionDate(obj.mInsertionDate), mDeadline(obj.mDeadline), mNumPomodoro(obj.mNumPomodoro), mOrder(obj.mOrder), mIsFinished(obj.mIsFinished) {
}
const Activity& Activity::operator=(const Activity& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        mDescription = obj.mDescription;
        mInsertionDate = obj.mInsertionDate;
        mDeadline = obj.mDeadline;
        mNumPomodoro = obj.mNumPomodoro;
        mOrder = obj.mOrder;
        mIsFinished = obj.mIsFinished;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string Activity::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(mDescription.name());
    values.push_back(mDescription);
    mDescription.setModified(false);
    fields.push_back(mInsertionDate.name());
    values.push_back(mInsertionDate);
    mInsertionDate.setModified(false);
    fields.push_back(mDeadline.name());
    values.push_back(mDeadline);
    mDeadline.setModified(false);
    fields.push_back(mNumPomodoro.name());
    values.push_back(mNumPomodoro);
    mNumPomodoro.setModified(false);
    fields.push_back(mOrder.name());
    values.push_back(mOrder);
    mOrder.setModified(false);
    fields.push_back(mIsFinished.name());
    values.push_back(mIsFinished);
    mIsFinished.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Activity::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Activity::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, mDescription);
    updateField(updates, table__, mInsertionDate);
    updateField(updates, table__, mDeadline);
    updateField(updates, table__, mNumPomodoro);
    updateField(updates, table__, mOrder);
    updateField(updates, table__, mIsFinished);
}
void Activity::addIDUpdates(Updates& updates) {
}
void Activity::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(MDescription);
    ftypes.push_back(MInsertionDate);
    ftypes.push_back(MDeadline);
    ftypes.push_back(MNumPomodoro);
    ftypes.push_back(MOrder);
    ftypes.push_back(MIsFinished);
}
void Activity::delRecord() {
    deleteFromTable(table__, id);
}
void Activity::delRelations() {
    ActivityInAIS::del(*db, (ActivityInAIS::Activity == id));
    ActivityInTTS::del(*db, (ActivityInTTS::Activity == id));
}
void Activity::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Activity::del() {
    if (typeIsCorrect() == false) {
        std::auto_ptr<Activity> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool Activity::typeIsCorrect() {
    return type == type__;
}
std::auto_ptr<Activity> Activity::upcast() {
    return auto_ptr<Activity>(new Activity(*this));
}
std::auto_ptr<Activity> Activity::upcastCopy() {
    Activity* np = NULL;
    np->id = id;
    np->type = type;
    np->mDescription = mDescription;
    np->mInsertionDate = mInsertionDate;
    np->mDeadline = mDeadline;
    np->mNumPomodoro = mNumPomodoro;
    np->mOrder = mOrder;
    np->mIsFinished = mIsFinished;
    np->inDatabase = inDatabase;
    if (!np)
        np = new Activity(*this);
    return auto_ptr<Activity>(np);
}
std::ostream & operator<<(std::ostream& os, Activity o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.mDescription.name() << " = " << o.mDescription << std::endl;
    os << o.mInsertionDate.name() << " = " << o.mInsertionDate << std::endl;
    os << o.mDeadline.name() << " = " << o.mDeadline << std::endl;
    os << o.mNumPomodoro.name() << " = " << o.mNumPomodoro << std::endl;
    os << o.mOrder.name() << " = " << o.mOrder << std::endl;
    os << o.mIsFinished.name() << " = " << o.mIsFinished << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType ActivityInventorySheet::Own::Id("id_","INTEGER","ActivityInventorySheet_");
const std::string ActivityInventorySheet::type__("ActivityInventorySheet");
const std::string ActivityInventorySheet::table__("ActivityInventorySheet_");
const std::string ActivityInventorySheet::sequence__("ActivityInventorySheet_seq");
const litesql::FieldType ActivityInventorySheet::Id("id_","INTEGER",table__);
const litesql::FieldType ActivityInventorySheet::Type("type_","TEXT",table__);
void ActivityInventorySheet::defaults() {
    id = 0;
}
ActivityInventorySheet::ActivityInventorySheet(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type) {
    defaults();
}
ActivityInventorySheet::ActivityInventorySheet(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type) {
    defaults();
    size_t size = (rec.size() > 2) ? 2 : rec.size();
    switch(size) {
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
ActivityInventorySheet::ActivityInventorySheet(const ActivityInventorySheet& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type) {
}
const ActivityInventorySheet& ActivityInventorySheet::operator=(const ActivityInventorySheet& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string ActivityInventorySheet::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void ActivityInventorySheet::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void ActivityInventorySheet::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
}
void ActivityInventorySheet::addIDUpdates(Updates& updates) {
}
void ActivityInventorySheet::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
}
void ActivityInventorySheet::delRecord() {
    deleteFromTable(table__, id);
}
void ActivityInventorySheet::delRelations() {
    ActivityInAIS::del(*db, (ActivityInAIS::ActivityInventorySheet == id));
}
void ActivityInventorySheet::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void ActivityInventorySheet::del() {
    if (typeIsCorrect() == false) {
        std::auto_ptr<ActivityInventorySheet> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool ActivityInventorySheet::typeIsCorrect() {
    return type == type__;
}
std::auto_ptr<ActivityInventorySheet> ActivityInventorySheet::upcast() {
    return auto_ptr<ActivityInventorySheet>(new ActivityInventorySheet(*this));
}
std::auto_ptr<ActivityInventorySheet> ActivityInventorySheet::upcastCopy() {
    ActivityInventorySheet* np = NULL;
    np->id = id;
    np->type = type;
    np->inDatabase = inDatabase;
    if (!np)
        np = new ActivityInventorySheet(*this);
    return auto_ptr<ActivityInventorySheet>(np);
}
std::ostream & operator<<(std::ostream& os, ActivityInventorySheet o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType TodoTodaySheet::Own::Id("id_","INTEGER","TodoTodaySheet_");
const std::string TodoTodaySheet::type__("TodoTodaySheet");
const std::string TodoTodaySheet::table__("TodoTodaySheet_");
const std::string TodoTodaySheet::sequence__("TodoTodaySheet_seq");
const litesql::FieldType TodoTodaySheet::Id("id_","INTEGER",table__);
const litesql::FieldType TodoTodaySheet::Type("type_","TEXT",table__);
void TodoTodaySheet::defaults() {
    id = 0;
}
TodoTodaySheet::TodoTodaySheet(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type) {
    defaults();
}
TodoTodaySheet::TodoTodaySheet(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type) {
    defaults();
    size_t size = (rec.size() > 2) ? 2 : rec.size();
    switch(size) {
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
TodoTodaySheet::TodoTodaySheet(const TodoTodaySheet& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type) {
}
const TodoTodaySheet& TodoTodaySheet::operator=(const TodoTodaySheet& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string TodoTodaySheet::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void TodoTodaySheet::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void TodoTodaySheet::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
}
void TodoTodaySheet::addIDUpdates(Updates& updates) {
}
void TodoTodaySheet::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
}
void TodoTodaySheet::delRecord() {
    deleteFromTable(table__, id);
}
void TodoTodaySheet::delRelations() {
    ActivityInTTS::del(*db, (ActivityInTTS::TodoTodaySheet == id));
}
void TodoTodaySheet::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void TodoTodaySheet::del() {
    if (typeIsCorrect() == false) {
        std::auto_ptr<TodoTodaySheet> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool TodoTodaySheet::typeIsCorrect() {
    return type == type__;
}
std::auto_ptr<TodoTodaySheet> TodoTodaySheet::upcast() {
    return auto_ptr<TodoTodaySheet>(new TodoTodaySheet(*this));
}
std::auto_ptr<TodoTodaySheet> TodoTodaySheet::upcastCopy() {
    TodoTodaySheet* np = NULL;
    np->id = id;
    np->type = type;
    np->inDatabase = inDatabase;
    if (!np)
        np = new TodoTodaySheet(*this);
    return auto_ptr<TodoTodaySheet>(np);
}
std::ostream & operator<<(std::ostream& os, TodoTodaySheet o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Settings::Own::Id("id_","INTEGER","Settings_");
const std::string Settings::type__("Settings");
const std::string Settings::table__("Settings_");
const std::string Settings::sequence__("Settings_seq");
const litesql::FieldType Settings::Id("id_","INTEGER",table__);
const litesql::FieldType Settings::Type("type_","TEXT",table__);
const litesql::FieldType Settings::MName("mName_","TEXT",table__);
const litesql::FieldType Settings::MValue("mValue_","TEXT",table__);
void Settings::defaults() {
    id = 0;
}
Settings::Settings(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), mName(MName), mValue(MValue) {
    defaults();
}
Settings::Settings(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), mName(MName), mValue(MValue) {
    defaults();
    size_t size = (rec.size() > 4) ? 4 : rec.size();
    switch(size) {
    case 4: mValue = convert<const std::string&, std::string>(rec[3]);
        mValue.setModified(false);
    case 3: mName = convert<const std::string&, std::string>(rec[2]);
        mName.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Settings::Settings(const Settings& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), mName(obj.mName), mValue(obj.mValue) {
}
const Settings& Settings::operator=(const Settings& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        mName = obj.mName;
        mValue = obj.mValue;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string Settings::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(mName.name());
    values.push_back(mName);
    mName.setModified(false);
    fields.push_back(mValue.name());
    values.push_back(mValue);
    mValue.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Settings::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Settings::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, mName);
    updateField(updates, table__, mValue);
}
void Settings::addIDUpdates(Updates& updates) {
}
void Settings::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(MName);
    ftypes.push_back(MValue);
}
void Settings::delRecord() {
    deleteFromTable(table__, id);
}
void Settings::delRelations() {
}
void Settings::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Settings::del() {
    if (typeIsCorrect() == false) {
        std::auto_ptr<Settings> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool Settings::typeIsCorrect() {
    return type == type__;
}
std::auto_ptr<Settings> Settings::upcast() {
    return auto_ptr<Settings>(new Settings(*this));
}
std::auto_ptr<Settings> Settings::upcastCopy() {
    Settings* np = NULL;
    np->id = id;
    np->type = type;
    np->mName = mName;
    np->mValue = mValue;
    np->inDatabase = inDatabase;
    if (!np)
        np = new Settings(*this);
    return auto_ptr<Settings>(np);
}
std::ostream & operator<<(std::ostream& os, Settings o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.mName.name() << " = " << o.mName << std::endl;
    os << o.mValue.name() << " = " << o.mValue << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
PomotuxDatabase::PomotuxDatabase(std::string backendType, std::string connInfo)
     : litesql::Database(backendType, connInfo) {
    initialize();
}
std::vector<litesql::Database::SchemaItem> PomotuxDatabase::getSchema() const {
    vector<Database::SchemaItem> res;
    res.push_back(Database::SchemaItem("schema_","table","CREATE TABLE schema_ (name_ TEXT, type_ TEXT, sql_ TEXT);"));
    if (backend->supportsSequences()) {
        res.push_back(Database::SchemaItem("Activity_seq","sequence","CREATE SEQUENCE Activity_seq START 1 INCREMENT 1"));
        res.push_back(Database::SchemaItem("ActivityInventorySheet_seq","sequence","CREATE SEQUENCE ActivityInventorySheet_seq START 1 INCREMENT 1"));
        res.push_back(Database::SchemaItem("TodoTodaySheet_seq","sequence","CREATE SEQUENCE TodoTodaySheet_seq START 1 INCREMENT 1"));
        res.push_back(Database::SchemaItem("Settings_seq","sequence","CREATE SEQUENCE Settings_seq START 1 INCREMENT 1"));
    }
    res.push_back(Database::SchemaItem("Activity_","table","CREATE TABLE Activity_ (id_ " + backend->getRowIDType() + ",type_ TEXT,mDescription_ TEXT,mInsertionDate_ INTEGER,mDeadline_ INTEGER,mNumPomodoro_ INTEGER,mOrder_ INTEGER,mIsFinished_ INTEGER)"));
    res.push_back(Database::SchemaItem("ActivityInventorySheet_","table","CREATE TABLE ActivityInventorySheet_ (id_ " + backend->getRowIDType() + ",type_ TEXT)"));
    res.push_back(Database::SchemaItem("TodoTodaySheet_","table","CREATE TABLE TodoTodaySheet_ (id_ " + backend->getRowIDType() + ",type_ TEXT)"));
    res.push_back(Database::SchemaItem("Settings_","table","CREATE TABLE Settings_ (id_ " + backend->getRowIDType() + ",type_ TEXT,mName_ TEXT,mValue_ TEXT)"));
    res.push_back(Database::SchemaItem("_06044cc54d2aba326c362937595d5709","table","CREATE TABLE _06044cc54d2aba326c362937595d5709 (Activity1 INTEGER UNIQUE,ActivityInventorySheet2 INTEGER)"));
    res.push_back(Database::SchemaItem("Activity_TodoTodaySheet_","table","CREATE TABLE Activity_TodoTodaySheet_ (Activity1 INTEGER UNIQUE,TodoTodaySheet2 INTEGER)"));
    res.push_back(Database::SchemaItem("_cb57b43da17da05f58b6c4cb99b69ab1","index","CREATE INDEX _cb57b43da17da05f58b6c4cb99b69ab1 ON _06044cc54d2aba326c362937595d5709 (Activity1)"));
    res.push_back(Database::SchemaItem("_a39a664b70ff48d2712a612321afe25a","index","CREATE INDEX _a39a664b70ff48d2712a612321afe25a ON _06044cc54d2aba326c362937595d5709 (ActivityInventorySheet2)"));
    res.push_back(Database::SchemaItem("_5e72e2d2961ee8074a50f61945b4d8d6","index","CREATE INDEX _5e72e2d2961ee8074a50f61945b4d8d6 ON _06044cc54d2aba326c362937595d5709 (Activity1,ActivityInventorySheet2)"));
    res.push_back(Database::SchemaItem("_819f6c8604a2ed951954e6d2e5783cff","index","CREATE INDEX _819f6c8604a2ed951954e6d2e5783cff ON Activity_TodoTodaySheet_ (Activity1)"));
    res.push_back(Database::SchemaItem("_7517cb999f4a2d220446a6e2fa66ccd7","index","CREATE INDEX _7517cb999f4a2d220446a6e2fa66ccd7 ON Activity_TodoTodaySheet_ (TodoTodaySheet2)"));
    res.push_back(Database::SchemaItem("_0cc98704fb046de91749a1aa7c6c4f96","index","CREATE INDEX _0cc98704fb046de91749a1aa7c6c4f96 ON Activity_TodoTodaySheet_ (Activity1,TodoTodaySheet2)"));
    return res;
}
void PomotuxDatabase::initialize() {
    static bool initialized = false;
    if (initialized)
        return;
    initialized = true;
}
}
