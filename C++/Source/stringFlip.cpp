vector<int> Solution::flip(string A)
{
    int numTotal1s = 0;
    int n = A.size();
    for (int i = 0; i < n; i++)
    {
        if (A[i] == '1')
            numTotal1s++;
    }
    int maxNumOf1s = numTotal1s;
    vector<int> retVec(2, -1);
    int num1sOutsideTheSet = 0;
    for (int i = 0; i < n; i++)
    {
        int num1sInTheSet = 0;
        if ((num1sOutsideTheSet + (n - i)) > maxNumOf1s)
        {
            for (int j = i; j < n; j++)
            {
                if (A[j] == '0')
                {
                    int setSize = j - i + 1;
                    //find the number of ones after flipping the set
                    int num1sInTheSetAfterFlipping = setSize - num1sInTheSet;
                    int totalNum1sAfterFlipping = numTotal1s - num1sInTheSet + num1sInTheSetAfterFlipping;
                    if (totalNum1sAfterFlipping > maxNumOf1s)
                    {
                        maxNumOf1s = totalNum1sAfterFlipping;
                        retVec[0] = i + 1;
                        retVec[1] = j + 1;
                    }
                }
                else
                    num1sInTheSet++;
            }
        }
        if (A[i] == '1')
            num1sOutsideTheSet++;
    }
    if (retVec[0] == -1)
        retVec.clear();
    return retVec;
}
