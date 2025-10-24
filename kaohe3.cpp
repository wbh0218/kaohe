#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Spaceship {
protected:
    string model;  
    int speed;     
    int energy;    
public:
    Spaceship(string m, int s, int e) : model(m), speed(s), energy(e) {}
    virtual ~Spaceship() {} 
    virtual void showStatus() {
        cout << "型号：" << model << "，速度：" << speed << "，能量：" << energy << endl;
    }
    virtual void action() = 0;  
};
class CargoShip : public Spaceship {
private:
    int cargoCapacity;  
public:
    CargoShip(string m, int s, int e, int c) : Spaceship(m, s, e), cargoCapacity(c) {}

    void action() override {
        cout << "运输飞船" << model << "正在装载货物！" << endl;
    }

    void loadCargo(int cargo) {
        if (cargo <= cargoCapacity) {
            cargoCapacity -= cargo;
            cout << "已装载" << cargo << "单位货物，剩余货物容量：" << cargoCapacity << endl;
        } else {
            cout << "货物数量超过剩余容量，无法装载！" << endl;
        }
    }
    void showStatus() override {
        Spaceship::showStatus();
        cout << "货物容量：" << cargoCapacity << endl;
    }
};
class BattleShip : public Spaceship {
private:
    int weaponPower;  
public:
    BattleShip(string m, int s, int e, int w) : Spaceship(m, s, e), weaponPower(w) {}
    void action() override {
        cout << "战斗飞船" << model << "奶龙武器威力：" << weaponPower << endl;
    }

    void fireLaser() {
        if (energy >= 20) {
            energy -= 20;
            cout << "战斗飞船" << model << "奶龙武器剩余能量：" << energy << endl;
        } else {
            cout << "能量不足，无法发射奶龙！" << endl;
        }
    }

    void showStatus() override {
        Spaceship::showStatus();
        cout << "武器威力：" << weaponPower << endl;
    }
};
class ExplorerShip : public Spaceship {
private:
    int scanRange;  
public:
    ExplorerShip(string m, int s, int e, int sr) : Spaceship(m, s, e), scanRange(sr) {}

    void action() override {
        cout << "探索飞船" << model << "正在扫描星球！扫描范围：" << scanRange << endl;
    }

    void scanPlanet() {
        if (energy >= 15) {
            energy -= 15;
            cout << "探索飞船" << model << "扫描星球完成！剩余能量：" << energy << endl;
        } else {
            cout << "能量不足，无法扫描星球！" << endl;
        }
    }
    void showStatus() override {
        Spaceship::showStatus();
        cout << "扫描范围：" << scanRange << endl;
    }
};
class SpaceshipFleet {
private:
    vector<Spaceship*> ships;  
    int cargoCount = 0;        
    int battleCount = 0;       
    int explorerCount = 0;     
public:
    ~SpaceshipFleet() {
        for (auto ship : ships) {
            delete ship;
        }
    }
    void addShip() {
        int type;
        string model;
        int speed, energy;

        cout << "请选择飞船类型（1-运输飞船 2-战斗飞船 3-探索飞船）：";
        cin >> type;
        cout << "请输入飞船型号：";
        cin >> model;
        cout << "请输入飞船速度：";
        cin >> speed;
        cout << "请输入飞船能量：";
        cin >> energy;

        if (type == 1) {
            int cargoCap;
            cout << "请输入货物容量：";
            cin >> cargoCap;
            ships.push_back(new CargoShip(model, speed, energy, cargoCap));
            cargoCount++;
        } else if (type == 2) {
            int weaponPow;
            cout << "请输入武器威力：";
            cin >> weaponPow;
            ships.push_back(new BattleShip(model, speed, energy, weaponPow));
            battleCount++;
        } else if (type == 3) {
            int scanR;
            cout << "请输入扫描范围：";
            cin >> scanR;
            ships.push_back(new ExplorerShip(model, speed, energy, scanR));
            explorerCount++;
        } else {
            cout << "类型选择错误！" << endl;
            return;
        }
        cout << "飞船添加成功！" << endl;
    }
    void rentShip() {
        if (ships.empty()) {
            cout << "当前没有飞船可租赁！" << endl;
            return;
        }
        cout << "请选择要租赁的飞船序号（1-" << ships.size() << "）：";
        int idx;
        cin >> idx;
        if (idx < 1 || idx > ships.size()) {
            cout << "序号选择错误！" << endl;
            return;
        }
        Spaceship* ship = ships[idx - 1];
        ship->action();
        if (CargoShip* cargo = dynamic_cast<CargoShip*>(ship)) {
            int cargoNum;
            cout << "请输入要装载的货物数量：";
            cin >> cargoNum;
            cargo->loadCargo(cargoNum);
        } else if (BattleShip* battle = dynamic_cast<BattleShip*>(ship)) {
            battle->fireLaser();
        } else if (ExplorerShip* explorer = dynamic_cast<ExplorerShip*>(ship)) {
            explorer->scanPlanet(); 
        }
        ships.erase(ships.begin() + idx - 1);
        cout << "飞船租赁成功！" << endl;
    }
    void showAllShips() {
        if (ships.empty()) {
            cout<< "当前飞船库为空！"<<endl;
            return;
        }
        cout<<"\n===== 飞船库当前飞船列表 ====="<<endl;
        for (int i=0;i<ships.size();i++) {
            cout<<"\n飞船序号："<<i+1<<endl;
            ships[i]->showStatus();  
        }
        cout << "==============================" << endl;
    }
};
int main() {
    SpaceshipFleet fleet;
    int choice;
    while (true) {
        cout<<"\n===== 飞船租赁系统 ====="<<endl;
        cout<<"1. 添加飞船  2. 租赁飞船  3. 查看所有飞船  4. 退出"<<endl;
        cout<<"请输入操作选择：";
        cin>>choice;
        switch(choice){
            case 1:
                fleet.addShip();
                break;
            case 2:
                fleet.rentShip();
                break;
            case 3:
                fleet.showAllShips();
                break;
            case 4:
                cout<< "系统退出，感谢使用！" << endl;
                return 0;
            default:
                cout << "操作选择错误，请重新输入！" << endl;
        }
    }
}
