#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
using namespace std;

// Function to convert a number from any base to base 10
long long convertToBase10(string value, int base) {
    long long result = 0;
    long long power = 1;
    for (int i = value.length() - 1; i >= 0; --i) {
        char c = value[i];
        if (isdigit(c)) {
            result += (c - '0') * power;
        } else {
            result += (c - 'A' + 10) * power;  // Handle letters for base > 10
        }
        power *= base;
    }
    return result;
}

// Function to perform Lagrange interpolation
double lagrangeInterpolation(vector<pair<int, long long>> points, int x_value) {
    int k = points.size();
    double result = 0;
    
    for (int i = 0; i < k; i++) {
        double term = points[i].second;
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term = term * (x_value - points[j].first) / (points[i].first - points[j].first);
            }
        }
        result += term;
    }
    return result;
}

int main() {
    // Test Case 1 JSON Data (Hardcoded for example)
    map<int, pair<int, string>> testCase1 = {
        {1, {10, "4"}},   // x = 1, base = 10, value = "4"
        {2, {2, "111"}},  // x = 2, base = 2, value = "111"
        {3, {10, "12"}},  // x = 3, base = 10, value = "12"
        {6, {4, "213"}}   // x = 6, base = 4, value = "213"
    };

    int n = 4; // Number of points provided
    int k = 3; // Minimum points needed (for polynomial degree k-1)

    vector<pair<int, long long>> decodedPoints;

    // Decode each y value from its respective base and store (x, y)
    for (auto &point : testCase1) {
        int x = point.first;
        int base = point.second.first;
        string value = point.second.second;
        long long y = convertToBase10(value, base);
        decodedPoints.push_back({x, y});
    }

    // Calculate the constant term using Lagrange interpolation at x = 0
    double constantC = lagrangeInterpolation(decodedPoints, 0);
    
    // Output the constant term (Secret C)
    cout << "Secret (Constant term c) = " << constantC << endl;

    // Test Case 2 - To handle wrong points
    map<int, pair<int, string>> testCase2 = {
        {1, {10, "28735619723837"}},
        {2, {16, "1A228867F0CA"}},
        {3, {12, "32811A4AA0B7B"}},
        {4, {11, "917978721331A"}},
        {5, {16, "1A22886782E1"}},
        {6, {10, "28735619654702"}},
        {7, {14, "71AB5070CC4B"}},
        {8, {9, "122662581541670"}},
        {9, {8, "642121030037605"}}
    };

    vector<pair<int, long long>> decodedPoints2;

    // Decode second test case
    for (auto &point : testCase2) {
        int x = point.first;
        int base = point.second.first;
        string value = point.second.second;
        long long y = convertToBase10(value, base);
        decodedPoints2.push_back({x, y});
    }

    // Calculate the constant term using Lagrange interpolation at x = 0
    double constantC2 = lagrangeInterpolation(decodedPoints2, 0);
    
    // Output the constant term for the second case
    cout << "Secret (Constant term c for Test Case 2) = " << constantC2 << endl;

    // Checking for wrong points (imposter points)
    vector<int> wrongPoints;
    for (auto &point : decodedPoints2) {
        double interpolatedY = lagrangeInterpolation(decodedPoints2, point.first);
        if (abs(interpolatedY - point.second) > 1e-6) {  // small tolerance for floating-point errors
            wrongPoints.push_back(point.first);
        }
    }

    // Output wrong points if any
    if (!wrongPoints.empty()) {
        cout << "Wrong Points: ";
        for (int x : wrongPoints) {
            cout << x << " ";
        }
        cout << endl;
    } else {
        cout << "No Wrong Points found!" << endl;
    }

    return 0;
}
