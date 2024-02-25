//
// Created by zysko on 18.02.2024.
//

#ifndef WITCH_H
#define WITCH_H



class Witch {
public:
    void TurnAround();
    bool CheckState() const;
    void Draw();
    void Reset();

private:
    bool m_IsLooking;
};



#endif //WITCH_H
