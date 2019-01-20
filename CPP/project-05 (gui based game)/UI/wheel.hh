#ifndef WHEEL_HH
#define WHEEL_HH

class wheel {
public:
    wheel();
    void spin();
    int getCurrentValue();

private:
    int currentValue;
};

#endif // WHEEL_HH
