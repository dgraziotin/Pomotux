#ifndef _pomotuxdatabase_hpp_
#define _pomotuxdatabase_hpp_
#include "litesql.hpp"
namespace pomotuxdatabase {
class Activity;
class ActivityInventorySheet;
class TodoTodaySheet;
class ActivityInAIS {
public:
    class Row {
    public:
        litesql::Field<int> activityInventorySheet;
        litesql::Field<int> activity;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Activity;
    static const litesql::FieldType ActivityInventorySheet;
    static void link(const litesql::Database& db, const pomotuxdatabase::Activity& o0, const pomotuxdatabase::ActivityInventorySheet& o1);
    static void unlink(const litesql::Database& db, const pomotuxdatabase::Activity& o0, const pomotuxdatabase::ActivityInventorySheet& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<ActivityInAIS::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
;
;
};
class ActivityInTTS {
public:
    class Row {
    public:
        litesql::Field<int> todoTodaySheet;
        litesql::Field<int> activity;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Activity;
    static const litesql::FieldType TodoTodaySheet;
    static void link(const litesql::Database& db, const pomotuxdatabase::Activity& o0, const pomotuxdatabase::TodoTodaySheet& o1);
    static void unlink(const litesql::Database& db, const pomotuxdatabase::Activity& o0, const pomotuxdatabase::TodoTodaySheet& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<ActivityInTTS::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
;
;
};
class Activity : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType MDescription;
    litesql::Field<std::string> mDescription;
    static const litesql::FieldType MInsertionDate;
    litesql::Field<litesql::Date> mInsertionDate;
    static const litesql::FieldType MDeadline;
    litesql::Field<litesql::Date> mDeadline;
    static const litesql::FieldType MNumPomodoro;
    litesql::Field<int> mNumPomodoro;
    static const litesql::FieldType MOrder;
    litesql::Field<int> mOrder;
    static const litesql::FieldType MIsFinished;
    litesql::Field<bool> mIsFinished;
protected:
    void defaults();
public:
    Activity(const litesql::Database& db);
    Activity(const litesql::Database& db, const litesql::Record& rec);
    Activity(const Activity& obj);
    const Activity& operator=(const Activity& obj);
    virtual void Delete(const litesql::Database& rDatabase, Activity& rCurrentActivity, ActivityInventorySheet& rAIS, TodoTodaySheet& rTTS);
    virtual void Modify(const litesql::Database& rDatabase, Activity& rCurrentActivity, int newDeadline, std::string newDescription);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect();
    std::auto_ptr<Activity> upcast();
    std::auto_ptr<Activity> upcastCopy();
};
std::ostream & operator<<(std::ostream& os, Activity o);
class ActivityInventorySheet : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
protected:
    void defaults();
public:
    ActivityInventorySheet(const litesql::Database& db);
    ActivityInventorySheet(const litesql::Database& db, const litesql::Record& rec);
    ActivityInventorySheet(const ActivityInventorySheet& obj);
    const ActivityInventorySheet& operator=(const ActivityInventorySheet& obj);
    virtual void InsertActivity(const litesql::Database& rDatabase, Activity& rNewActivity, ActivityInventorySheet& rAIS);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect();
    std::auto_ptr<ActivityInventorySheet> upcast();
    std::auto_ptr<ActivityInventorySheet> upcastCopy();
};
std::ostream & operator<<(std::ostream& os, ActivityInventorySheet o);
class TodoTodaySheet : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
protected:
    void defaults();
public:
    TodoTodaySheet(const litesql::Database& db);
    TodoTodaySheet(const litesql::Database& db, const litesql::Record& rec);
    TodoTodaySheet(const TodoTodaySheet& obj);
    const TodoTodaySheet& operator=(const TodoTodaySheet& obj);
    virtual void ScheduleActivity(const litesql::Database& rDatabase, Activity& rNewActivity, ActivityInventorySheet& rAIS, TodoTodaySheet& rTTS);
    virtual void FinishActivity(const litesql::Database& rDatabase, Activity& rCurrentActivity, TodoTodaySheet& rTTS);
    virtual void PostponeActivity(const litesql::Database& rDatabase, Activity& rCurrentActivity, TodoTodaySheet& rTTS);
    virtual void MoveActivity(const litesql::Database& rDatabase, Activity& rCurrentActivity, TodoTodaySheet& rCurrentTDS, const int direction);
    virtual int GetMaxActivityOrder(const litesql::Database& rDatabase, TodoTodaySheet& rTTS);
    virtual void MakeConsistent(const litesql::Database& rDatabase, TodoTodaySheet& rTTS);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect();
    std::auto_ptr<TodoTodaySheet> upcast();
    std::auto_ptr<TodoTodaySheet> upcastCopy();
};
std::ostream & operator<<(std::ostream& os, TodoTodaySheet o);
class PomotuxDatabase : public litesql::Database {
public:
    PomotuxDatabase(std::string backendType, std::string connInfo);
protected:
    virtual std::vector<litesql::Database::SchemaItem> getSchema() const;
    static void initialize();
};
}
#endif
