#include <iostream>

enum Outcome {
    SUCCESS,
    FAIL_RETURN,
    FAIL_THROW
};

// Demo disk storage, does nothing useful but may throw exception.
class Storage {
public:
    Storage()
        : i_(0)
    {
    }
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
class Index {
public:
    Index()
        : i_(0)
    {
    }
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

    class StorageGuard {
    public:
        StorageGuard(Storage& S)
            : S_(S)
            , commit_(false)
        {
        }
        ~StorageGuard()
        {
            if (!commit_)
                S_.undo();
        }
        void commit() noexcept { commit_ = true; }

    private:
        Storage& S_;
        bool commit_;
        StorageGuard(const StorageGuard&) = delete;
        StorageGuard& operator=(const StorageGuard&) = delete;
    };

    class StorageFinalizer {
    public:
        StorageFinalizer(Storage& S)
            : S_(S)
        {
        }
        ~StorageFinalizer() { S_.finalize(); }

    private:
        Storage& S_;
    };

    try {
        // Declarative. No flow control. No ugly nested try-catch blocks. Looks very nice!
        S.insert(42, SUCCESS);
        StorageFinalizer SF(S);
        StorageGuard SG(S);
        I.insert(42, FAIL_THROW);
        SG.commit();
    } catch (...) {
        std::cout << "Index insertion failed. But we're still cool!" << std::endl;
    }

    if (S.get() != I.get())
        std::cout << "Inconsistent state: " << S.get() << " != " << I.get() << std::endl;
    else
        std::cout << "Database OK" << std::endl;
}
