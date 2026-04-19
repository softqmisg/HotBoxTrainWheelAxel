#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    // Save/load carNumber
    void saveCarNumber(int carNum);
    int  getCarNumber() const;



protected:

private:
    ModelListener* modelListener;
    int saveCarNumberValue;
};

#endif // MODEL_HPP
