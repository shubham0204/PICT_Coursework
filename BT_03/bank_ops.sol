// SPDX-License-Identifier: GPL-3.0

pragma solidity >=0.7.0 <0.9.0;

contract BankOperations {

    event Deposit(uint256 amount);
    event Withdraw(uint256 amount);

    uint256 private balance;

    constructor() {
        balance = 0;
    }

    function deposit() public payable {
        balance += msg.value;
        emit Deposit(msg.value);
    }

    function withdraw(uint256 amount) public {
        require(amount <= balance, "Insufficient balance");
        balance -= amount;
        payable(msg.sender).transfer(amount);
        emit Withdraw(amount);
    }

    function getBalance() public view returns (uint256) {
        return balance;
    }

}