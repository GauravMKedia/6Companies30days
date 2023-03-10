// https://leetcode.com/problems/number-of-pairs-satisfying-inequality/description/
class Solution {
public:
    typedef long long ll;
    
    class SegmentTree {
        public:
        int maxN;
        vector<ll> seg;
        
        SegmentTree(int n) : maxN(n) {
            seg = vector<ll> (maxN * 4 + 10, 0);
        }
        
        ll query(int l, int r) {
            return query_util(0, 0, maxN - 1, l, r);
        }
        
        ll query_util(int i, int low, int high, int l, int r) {
            if(low >= l && high <= r) 
                return seg[i];
            if(l > high || r < low)
                return 0;
            int mid = (low + high) / 2;
            ll left = query_util(2 * i + 1, low, mid, l, r);
            ll right = query_util(2 * i + 2, mid + 1, high, l, r);
            return left + right;
        }
        
        void update(int ele) {
            update_util(0, 0, maxN - 1, ele);
        }
        
        void update_util(int i, int low, int high, int ele) {
            if(low == high) {
                seg[i]++;
                return;
            }
            int mid = (low + high) / 2;
            if(ele <= mid) {
                update_util(2 * i + 1, low, mid, ele);
            } else {
                update_util(2 * i + 2, mid + 1, high, ele);
            }
            seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
        }
    };
    
    long long numberOfPairs(vector<int>& nums, vector<int>& nums2, int diff) {
        int n = nums.size();
        int offset = 20000;
        int max_ele = nums[0];
        for(int i = 0; i < n; i++) {
            nums[i] -= nums2[i];
            max_ele = max(max_ele, nums[i]);
        }
        SegmentTree seg(max_ele + offset + 1);
        ll ans = 0;
        for(auto it : nums) {
            ll count = seg.query(0, it + diff + offset);
            ans += count;
            seg.update(it + offset);
        }
        return ans;
    }
};