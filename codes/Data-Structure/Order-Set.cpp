// .find_by_order(k) 回傳第 k 小的值（based-0）
// .order_of_key(k) 回傳有多少元素比 k 小

#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> order_set;