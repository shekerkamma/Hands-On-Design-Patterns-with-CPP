#include <iostream>

enum Outcome
{
    SUCCESS,
    FAIL_RETURN,
    FAIL_THROW
};

// Demo disk storage, does nothing useful but may throw exception.
class Storage
{
public:
    Storage() : i_(0), finalized_(false) {}
    bool insert(int i, Outcome outcome)
    {
        if (outcome == FAIL_THROW)
            throw 0;
        if (outcome == FAIL_RETURN)
            return false;
        i1_ = i_;
        i_ = i;
        return true;
    }
    void undo()
    {
        i_ = i1_;
    }
    void finalize() { finalized_ = true; }
    bool finalized() const { return finalized_; }
    int get() const { return i_; }

private:
    int i_;
    int i1_;
    bool finalized_;
};

// Demo memory index, does nothing useful but may throw exception.
class Index
{
public:
    Index() : i_(0) {}
    bool insert(int i, Outcome outcome)
    {
        if (outcome == FAIL_THROW)
            throw 0;
        if (outcome == FAIL_RETURN)
            return false;
        i1_ = i_;
        i_ = i;
        return true;
    }
    void undo()
    {
        i_ = i1_;
    }
    int get() const { return i_; }

private:
    int i_;
    int i1_;
};

int main()
{
    Storage S;
    Index I;

    // This is the only difference to 02a_trycatch_cleanup.cpp
    // But class StorageFinalizer not used. So result obviously the same.
    class StorageFinalizer
    {
    public:
        StorageFinalizer(Storage &S) : S_(S) {}
        ~StorageFinalizer() { S_.finalize(); }

    private:
        Storage &S_;
    };

    try
    {
        S.insert(42, SUCCESS);
        try
        {
            I.insert(42, FAIL_THROW);
        }
        catch (...)
        {
            S.undo();
        }
        S.finalize();
    }
    catch (...)
    {
    }

    if (S.get() != I.get())
        std::cout << "Inconsistent state: " << S.get() << " != " << I.get() << std::endl;
    else if (!S.finalized())
        std::cout << "Not finalized" << std::endl;
    else
        std::cout << "Database OK" << std::endl;
}
