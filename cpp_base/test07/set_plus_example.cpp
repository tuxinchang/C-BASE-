#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// 自定义类：学生
class Student {
private:
    string name;
    int id;
    double score;
    
public:
    // 构造函数
    Student(string n, int i, double s) : name(n), id(i), score(s) {}
    
    // 获取私有成员的方法
    string getName() const { return name; }
    int getId() const { return id; }
    double getScore() const { return score; }
    
    // 重载输出运算符，方便输出
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << "[" << s.id << "] " << s.name << " - 成绩: " << s.score;
        return os;
    }
};

// ================== 方式1：使用仿函数（函数对象）作为比较器 ==================
// 按成绩降序排序
struct CompareByScoreDesc {
    bool operator()(const Student& s1, const Student& s2) const {
        // 成绩高的排在前面
        if (s1.getScore() != s2.getScore()) {
            return s1.getScore() > s2.getScore(); // 降序
        }
        // 成绩相同按学号升序
        return s1.getId() < s2.getId();
    }
};

// 按学号升序排序
struct CompareById {
    bool operator()(const Student& s1, const Student& s2) const {
        return s1.getId() < s2.getId();
    }
};

// 按姓名升序排序
struct CompareByName {
    bool operator()(const Student& s1, const Student& s2) const {
        return s1.getName() < s2.getName();
    }
};

// ================== 方式2：使用Lambda表达式（需要在set声明时传递） ==================

// ================== 方式3：重载<运算符（不推荐，因为只能有一种排序规则） ==================

int main() {
    cout << "=== C++ set 存取自定义数据类型（类）并自定义排序 ===" << endl << endl;
    
    // 创建学生数据
    vector<Student> students = {
        Student("张三", 1001, 85.5),
        Student("李四", 1002, 92.0),
        Student("王五", 1003, 78.5),
        Student("赵六", 1004, 92.0),  // 与李四成绩相同
        Student("钱七", 1005, 88.0),
        Student("孙八", 1006, 78.5)   // 与王五成绩相同
    };
    
    cout << "原始学生数据:" << endl;
    for (const auto& s : students) {
        cout << s << endl;
    }
    cout << endl;
    
    // ================== 示例1：按成绩降序排序 ==================
    cout << "1. 按成绩降序排序 (成绩相同按学号升序):" << endl;
    set<Student, CompareByScoreDesc> setByScoreDesc;
    
    // 插入所有学生
    for (const auto& s : students) {
        setByScoreDesc.insert(s);
    }
    
    // 输出排序结果
    for (const auto& s : setByScoreDesc) {
        cout << s << endl;
    }
    cout << endl;
    
    // ================== 示例2：按学号升序排序 ==================
    cout << "2. 按学号升序排序:" << endl;
    set<Student, CompareById> setById;
    
    for (const auto& s : students) {
        setById.insert(s);
    }
    
    for (const auto& s : setById) {
        cout << s << endl;
    }
    cout << endl;
    
    // ================== 示例3：按姓名升序排序 ==================
    cout << "3. 按姓名升序排序 (中文按拼音顺序):" << endl;
    set<Student, CompareByName> setByName;
    
    for (const auto& s : students) {
        setByName.insert(s);
    }
    
    for (const auto& s : setByName) {
        cout << s << endl;
    }
    cout << endl;
    
    // ================== 示例4：使用Lambda表达式作为比较器 ==================
    cout << "4. 使用Lambda表达式排序 (先按成绩，再按姓名):" << endl;
    
    // 注意：Lambda表达式不能直接作为模板参数，需要使用decltype或函数指针
    // 方法1：使用decltype和函数对象
    auto compareByScoreThenName = [](const Student& s1, const Student& s2) {
        if (s1.getScore() != s2.getScore()) {
            return s1.getScore() > s2.getScore(); // 成绩降序
        }
        return s1.getName() < s2.getName(); // 姓名升序
    };
    
    // 使用decltype获取Lambda的类型
    set<Student, decltype(compareByScoreThenName)> setByLambda(compareByScoreThenName);
    
    for (const auto& s : students) {
        setByLambda.insert(s);
    }
    
    for (const auto& s : setByLambda) {
        cout << s << endl;
    }
    cout << endl;
    
    // ================== 示例5：复杂排序规则 ==================
    cout << "5. 复杂排序规则 (成绩分段排序):" << endl;
    
    // 定义复杂比较器：90分以上为优秀，80-89为良好，其他为一般
    struct CompareByGradeLevel {
        // 获取成绩等级
        int getGradeLevel(double score) const {
            if (score >= 90.0) return 1; // 优秀
            else if (score >= 80.0) return 2; // 良好
            else return 3; // 一般
        }
        
        bool operator()(const Student& s1, const Student& s2) const {
            int level1 = getGradeLevel(s1.getScore());
            int level2 = getGradeLevel(s2.getScore());
            
            // 先按成绩等级排序（优秀在前）
            if (level1 != level2) {
                return level1 < level2;
            }
            
            // 同一等级内按成绩降序
            if (s1.getScore() != s2.getScore()) {
                return s1.getScore() > s2.getScore();
            }
            
            // 成绩相同按学号升序
            return s1.getId() < s2.getId();
        }
    };
    
    set<Student, CompareByGradeLevel> setByGradeLevel;
    
    for (const auto& s : students) {
        setByGradeLevel.insert(s);
    }
    
    // 按等级输出
    int currentLevel = -1;
    for (const auto& s : setByGradeLevel) {
        int level = CompareByGradeLevel().getGradeLevel(s.getScore());
        if (level != currentLevel) {
            currentLevel = level;
            string levelStr;
            switch (level) {
                case 1: levelStr = "优秀(90分以上)"; break;
                case 2: levelStr = "良好(80-89分)"; break;
                case 3: levelStr = "一般(80分以下)"; break;
            }
            cout << "\n=== " << levelStr << " ===" << endl;
        }
        cout << s << endl;
    }
    cout << endl;
    
    // ================== 示例6：查找和删除操作 ==================
    cout << "6. 查找和删除操作:" << endl;
    
    set<Student, CompareById> studentSet;
    for (const auto& s : students) {
        studentSet.insert(s);
    }
    
    cout << "初始set大小: " << studentSet.size() << endl;
    
    // 查找学号为1003的学生
    Student searchStudent("", 1003, 0); // 只关心id，用于比较
    auto it = studentSet.find(searchStudent);
    if (it != studentSet.end()) {
        cout << "找到学生: " << *it << endl;
        
        // 删除该学生
        studentSet.erase(it);
        cout << "删除后set大小: " << studentSet.size() << endl;
    }
    
    // 查找成绩大于85分的学生
    cout << "\n成绩大于85分的学生:" << endl;
    for (const auto& s : studentSet) {
        if (s.getScore() > 85.0) {
            cout << s << endl;
        }
    }
    cout << endl;
    
    // ================== 示例7：存储指针的自定义比较 ==================
    cout << "7. 存储指针的自定义比较:" << endl;
    
    // 当存储指针时，需要自定义比较器来比较指针指向的对象
    struct CompareStudentPtr {
        bool operator()(const Student* s1, const Student* s2) const {
            // 先按成绩降序，再按姓名升序
            if (s1->getScore() != s2->getScore()) {
                return s1->getScore() > s2->getScore();
            }
            return s1->getName() < s2->getName();
        }
    };
    
    set<Student*, CompareStudentPtr> studentPtrSet;
    
    // 动态创建学生对象
    vector<Student*> studentPtrs = {
        new Student("张三", 1001, 85.5),
        new Student("李四", 1002, 92.0),
        new Student("王五", 1003, 78.5),
        new Student("赵六", 1004, 92.0),
        new Student("钱七", 1005, 88.0)
    };
    
    // 插入到set中
    for (auto ptr : studentPtrs) {
        studentPtrSet.insert(ptr);
    }
    
    // 输出排序结果
    cout << "按指针存储的set排序结果:" << endl;
    for (const auto& ptr : studentPtrSet) {
        cout << *ptr << endl;
    }
    
    // 释放动态分配的内存
    for (auto ptr : studentPtrs) {
        delete ptr;
    }
    cout << endl;
    
    // ================== 示例8：嵌套自定义类型的set ==================
    cout << "8. 嵌套自定义类型的set (班级中的学生组):" << endl;
    
    // 自定义班级类
    class Class {
    private:
        string className;
        set<Student, CompareByScoreDesc> students;
        
    public:
        Class(string name) : className(name) {}
        
        void addStudent(const Student& s) {
            students.insert(s);
        }
        
        void display() const {
            cout << "=== 班级: " << className << " (按成绩排序) ===" << endl;
            for (const auto& s : students) {
                cout << s << endl;
            }
        }
        
        // 重载<运算符，用于set排序
        bool operator<(const Class& other) const {
            return className < other.className;
        }
    };
    
    // 创建班级set，按班级名称排序
    set<Class> classSet;
    
    Class class1("一班");
    class1.addStudent(Student("张三", 1001, 85.5));
    class1.addStudent(Student("李四", 1002, 92.0));
    class1.addStudent(Student("王五", 1003, 78.5));
    
    Class class2("二班");
    class2.addStudent(Student("赵六", 1004, 88.0));
    class2.addStudent(Student("钱七", 1005, 95.0));
    class2.addStudent(Student("孙八", 1006, 82.5));
    
    classSet.insert(class1);
    classSet.insert(class2);
    
    // 输出所有班级
    for (const auto& cls : classSet) {
        cls.display();
        cout << endl;
    }
    
    // ================== 示例9：性能测试和注意事项 ==================
    cout << "9. 性能测试和注意事项:" << endl;
    
    // 创建大量数据测试性能
    set<Student, CompareById> largeSet;
    const int NUM_STUDENTS = 10000;
    
    cout << "插入 " << NUM_STUDENTS << " 个学生..." << endl;
    for (int i = 0; i < NUM_STUDENTS; ++i) {
        int id = 2000 + i;
        double score = 60.0 + (rand() % 400) / 10.0; // 60-100之间的随机分数
        largeSet.insert(Student("学生" + to_string(i), id, score));
    }
    cout << "插入完成，set大小: " << largeSet.size() << endl;
    
    
    
    return 0;
}