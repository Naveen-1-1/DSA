#include <bits/stdc++.h>
using namespace std;

struct btnode {
  btnode *lc;
  int val;
  btnode *rc;
};

typedef struct btnode *btptr;
btptr root = 0;

btptr create(int x) {
  btptr t = new (btnode);
  t->val = x;
  t->lc = t->rc = 0;
  return t;
}

int nodeheight(btptr t) {
  if (t)
    return 1 + max(nodeheight(t->rc), nodeheight(t->lc));
  else
    return 0;
}

int balancefactor(btptr t) {
  if (t != 0)
    return nodeheight(t->rc) - nodeheight(t->lc);
  else
    return 0;
}

btptr rrrotation(btptr p, btptr c) {
  p->rc = c->lc;
  c->lc = p;
  return c;
}

btptr llrotation(btptr p, btptr c) {
  p->lc = c->rc;
  c->rc = p;
  return c;
}

btptr rlrotation(btptr p, btptr c) {
  p->rc = llrotation(c, c->lc);
  return rrrotation(p, p->rc);
}

btptr lrrotation(btptr p, btptr c) {
  p->lc = rrrotation(c, c->rc);
  return llrotation(p, p->lc);
}

btptr add(btptr t, int x) {
  if (!t) {
    btptr temp = create(x);
    return temp;
  } else {
    int f = 0;
    if (x > t->val) {
      t->rc = add(t->rc, x);
      f = 1;
    } else
      t->lc = add(t->lc, x);
    btptr c = t->lc;
    if (f)
      c = t->rc;
    if (balancefactor(t) == 2 && balancefactor(c) == 1)
      t = rrrotation(t, c);
    else if (balancefactor(t) == 2 && balancefactor(c) == -1)
      t = rlrotation(t, c);
    else if (balancefactor(t) == -2 && balancefactor(c) == -1)
      t = llrotation(t, c);
    else if (balancefactor(t) == -2 && balancefactor(c) == 1)
      t = lrrotation(t, c);
    return t;
  }
}

btptr del(btptr t, int x) {
  if (t->val == x)
    return 0;
  else {
    int f = 0;
    if (x > t->val) {
      t->rc = del(t->rc, x);
      f = 1;
    } else
      t->lc = del(t->lc, x);
    btptr c = t->rc;
    if (f)
      c = t->lc;
    if (balancefactor(t) == 2 && balancefactor(c) == 1)
      t = rrrotation(t, c);
    else if (balancefactor(t) == 2 && balancefactor(c) == -1)
      t = rlrotation(t, c);
    else if (balancefactor(t) == 2 && balancefactor(c) == 0)
      t = rrrotation(t, c);
    else if (balancefactor(t) == -2 && balancefactor(c) == -1)
      t = llrotation(t, c);
    else if (balancefactor(t) == -2 && balancefactor(c) == 1)
      t = lrrotation(t, c);
    else if (balancefactor(t) == -2 && balancefactor(c) == 0)
      t = llrotation(t, c);
    return t;
  }
}

void level(queue<btptr> q) {
  if (!q.empty()) {
    btptr t = q.front();
    q.pop();
    if (t->val == -1) {
      cout << endl;
      if (!q.empty())
        q.push(t);
    } else {
      cout << t->val << " ";
      if (t->lc)
        q.push(t->lc);
      if (t->rc)
        q.push(t->rc);
    }
    level(q);
  }
}

void preorder(btptr t) {
  if (t) {
    cout << t->val << " ";
    preorder(t->lc);
    preorder(t->rc);
  }
}

int main() {
  btptr t = 0;
  cout << "Enter elements: -1 to break " << endl;
  int x;
  while (1) {
    cin >> x;
    if (x == -1)
      break;
    t = add(t, x);
  }
  btptr marker = create(-1);
  queue<btptr> q, qd;
  q.push(t), q.push(marker);
  cout << "Level order: " << endl;
  level(q);
  cout << "Pre order: " << endl;
  preorder(t);
  cout << endl << "Enter elements to delete: -1 to break: " << endl;
  while (1) {
    cin >> x;
    if (x == -1)
      break;
    t = del(t, x);
    qd.push(t), qd.push(marker);
    cout << "Level order: " << endl;
    level(q);
    cout << "Pre order: " << endl;
    preorder(t);
    cout << endl;
  }
  return 0;
}
