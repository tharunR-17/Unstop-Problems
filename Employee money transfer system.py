def can_pay_salaries(company_money, employee_names, employee_salaries):

    n=len(employee_salaries)
    s=0
    l=[]
    for i in range(n):
        if(employee_salaries[i]<=company_money):
            s=company_money-employee_salaries[i]
            # if(s>=0):
            company_money=s
            l.append("true")
        else:
            l.append("false")
        
    return l

def main():
    import sys
    input = sys.stdin.read
    data = input().strip().split('\n')
    
    company_money = int(data[0])  # First line is the amount of money in the company's bank account
    employee_count = int(data[1])  # Second line is the number of employees
    employee_names = data[2].split()  # Third line is the array of employee names
    employee_salaries = list(map(int, data[3].split()))  # Fourth line is the array of employee salaries
    
    # Call user logic function and get the result
    result = can_pay_salaries(company_money, employee_names, employee_salaries)
    
    # Print the output as space-separated boolean values
    print(' '.join(map(str, result)))

if __name__ == "__main__":
    main()
