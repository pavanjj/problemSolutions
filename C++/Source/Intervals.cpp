#include "./headers/commonHeaders.h"

struct Interval
{
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

int searchIntervals(vector<Interval> &intervals, Interval &newInterval)
{
    int start = 0;
    int end = intervals.size() - 1;
    int mid = (start + end) / 2;
    int prevStart = start;
    while (start <= end)
    {
        print("start", start);
        print("end", end);
        print("mid", mid);
        if (intervals[mid].start < newInterval.start)
        {
            start = mid + 1;
        }
        else if (intervals[mid].start > newInterval.start)
        {
            end = mid - 1;
        }
        else
        {
            return mid;
        }
        mid = (start + end) / 2;
    }
    return max(start - 1, 0);
}

bool checkOverlapAndMerge(Interval &srcInt, Interval &destInt)
{
    if ((destInt.start < srcInt.start && destInt.end > srcInt.end) ||
        (destInt.start >= srcInt.start && destInt.start <= srcInt.end) ||
        (destInt.end <= srcInt.end && destInt.end >= srcInt.start))
    {
        destInt.start = min(srcInt.start, destInt.start);
        destInt.end = max(srcInt.end, destInt.end);
        return true;
    }
    return false;
}

vector<Interval> insertAndMergeTheInterval(vector<Interval> &intervals, Interval &newInterval, int index)
{
    vector<Interval> mergedIntervals;
    int numIntervals = intervals.size();

    int skip = 1;
    for (int i = 0; i < index; i++)
        mergedIntervals.push_back(intervals[i]);

    if (!checkOverlapAndMerge(intervals[index], newInterval))
    {
        if (index == 0 && intervals[index].start > newInterval.start)
        {
            mergedIntervals.push_back(newInterval);
            newInterval = intervals[index];
        }
        else
            mergedIntervals.push_back(intervals[index]);
    }

    for (int i = index + 1; i < numIntervals; i++)
    {
        if (!checkOverlapAndMerge(intervals[i], newInterval))
            break;
        skip++;
    }

    mergedIntervals.push_back(newInterval);

    for (int i = index + skip; i < numIntervals; i++)
        mergedIntervals.push_back(intervals[i]);

    return mergedIntervals;
}

vector<Interval> insert(vector<Interval> &intervals, Interval newInterval)
{
    //do a binary seach on start times and find the correct place to insert
    vector<Interval> retVector;
    if (intervals.size() == 0)
        retVector.push_back(newInterval);
    else
    {
        int index = searchIntervals(intervals, newInterval);
        print("Index from BS ", index);
        retVector = insertAndMergeTheInterval(intervals, newInterval, index);
    }
    return retVector;
}

void main()
{
    vector<vector<int>> A{
        {851002, 1548832}, {1824775, 2342899}, {3701296, 4355961}, {6029828, 6182080}, {6819905, 7068746}, {7362197, 7610410}, {8642017, 10283019}, {11084369, 11471865}, {11817437, 12515059}, {12647297, 13579260}, {13604935, 13988374}, {14630856, 15160445}, {15352357, 15986696}, {16109934, 16711859}, {16764645, 17674228}, {18763815, 19185316}, {19805734, 21300345}, {23488411, 24964459}, {24987575, 26204041}, {26569241, 27107900}, {27479059, 27732209}, {27740436, 28049001}, {29019906, 29240348}, {29313043, 29918710}, {29931305, 30270618}, {30454126, 30856727}, {30865643, 31201076}, {31319820, 31484827}, {31618852, 32179664}, {32997802, 33233265}, {33677192, 34199956}, {34964678, 35512330}, {35950922, 36255383}, {36950793, 37607508}, {40130987, 40493231}, {42355930, 42730345}, {43203318, 43535958}, {43625841, 43711056}, {43951871, 44151006}, {44825308, 45003377}, {46231214, 46360598}, {47748832, 48715234}, {49210777, 50158351}, {50541768, 50839277}, {51521154, 52010917}, {53295317, 53935770}, {54298936, 54997194}, {55470872, 56353654}, {57095122, 57345475}, {59011840, 59580656}, {59886955, 60585442}, {61534903, 62189559}, {62543857, 63289267}, {63402371, 63644595}, {63998012, 64173879}, {64941139, 65500321}, {66568265, 67399830}, {69172240, 69221417}, {71547717, 71777020}, {71840953, 74197466}, {76131172, 76756276}, {77312574, 77385103}, {79181798, 80518323}, {81244054, 82398962}, {83669949, 84738725}, {85999692, 87107859}, {87572104, 87987373}, {91055370, 91117204}, {92515522, 93147310}, {93312665, 93711778}, {93757124, 94416459}, {96187030, 96864075}, {96909277, 97012027}, {99089805, 99225584}};
    vector<Interval> intervals;
    for (int i = 0; i < A.size(); i++)
    {
        intervals.push_back(Interval(A[i][0], A[i][1]));
    }
    auto intervals1 = insert(intervals, Interval(28039458, 40388967));
    for (int i = 0; i < intervals1.size(); i++)
    {
        cout << " i =" << intervals1[i].start << "," << intervals1[i].end << endl;
    }
}