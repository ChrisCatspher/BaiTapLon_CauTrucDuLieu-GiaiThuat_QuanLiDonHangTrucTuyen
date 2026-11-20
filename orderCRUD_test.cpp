check(!manager.cancelFrontOrder(), "queue should be empty");
}

void testDisplay() {
    OrderManager manager;
    // Chuyen noi dung cout vao output de kiem tra sau.
    ostringstream output;
    const auto flags = cout.flags();
    const auto precision = cout.precision();
    auto* original = cout.rdbuf(output.rdbuf());

    manager.displayAllOrders();
    manager.displayOrder("MISSING");
    const bool addedFirst = manager.addOrder(Order("DH01", "Ngoc Ngan", 20, 11, 2026, 125000, ChoPheDuyet));
    const bool addedSecond = manager.addOrder(Order("DH02", "Customer 2", 21, 11, 2026, 200000, ChoPheDuyet));
    manager.displayOrder("DH01");
    const string single = output.str();
    output.str("");
    manager.displayAllOrders();
    const string all = output.str();

    cout.rdbuf(original);
    cout.flags(flags);
    cout.precision(precision);

    check(addedFirst && addedSecond, "could not prepare display data");
    check(single.find("dang rong") != string::npos && single.find("MISSING") != string::npos, "empty and missing messages");
    check(single.find("DH01") != string::npos && single.find("DH02") == string::npos, "display one order");
    check(single.find("20/11/2026") != string::npos && single.find("125000") != string::npos &&
          single.find("Ngoc Ngan") != string::npos && single.find("Cho phe duyet") != string::npos, "display order fields");
    check(all.find("DH01") < all.find("DH02") && all.find("DH02") != string::npos, "display both orders in insertion order");
}
}

int main() {
    try {
        testAddAndFind();
        testInvalidInput();
        testDeleteAndQueue();
        testDisplay();
        cout << "PASS: order CRUD tests\n";
    } catch (const exception& error) {
        cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
