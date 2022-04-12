# report



## MySolver

首先找出 `entry` 和 `exit` 基本块，然后使用标准的数据流算法，代码如下：

```java
        boolean changed = true;
        while (changed) {
            changed = false;
            for (QuadIterator qit = new QuadIterator(cfg); qit.hasNext(); ) {
                Quad q = qit.next();
                Flow.DataflowObject oldIn = analysis.getIn(q), oldOut = analysis.getOut(q);
                Flow.DataflowObject newMeet = forward ?
                        meet(qit.predecessors1(), analysis.getEntry()) :
                        meet(qit.successors1(), analysis.getExit());
                if (forward) {
                    analysis.setIn(q, newMeet);
                } else {
                    analysis.setOut(q, newMeet);
                }
                analysis.processQuad(q);
                Flow.DataflowObject newIn = analysis.getIn(q), newOut = analysis.getOut(q);
                changed |= !newIn.equals(oldIn) || !newOut.equals(oldOut);
            }
            if (forward) {
                analysis.setExit(meet(exitQ, analysis.getEntry()));
            } else {
                analysis.setEntry(analysis.getIn(entryQ));
            }
        }
```

在每个循环中，遍历所有基本块，首先进行 `meet`，这里需要根据前向后向传入不同的参数，第一个参数是需要遍历的块，第二个参数是如果该块为`null`（即出入口边界）时应该设为什么数据；然后再 `processQuad`，即使用 `transferfn`；最后再根据方向设定 `entry/exit`。直到某次循环中没有数据发生变化。



## ReachingDefs

整体的实现思路比较简单，除了方向和Domin外和 `Liveness` 很类似。需要在预处理阶段构建一个从变量到定义块的表，以方便 kill 的实现，核心方法为 `processQuad`，代码如下：

```java
    public void processQuad(Quad q) {
        DefIDSet newOut = (DefIDSet) getIn(q);
        for (Operand.RegisterOperand def : q.getDefinedRegisters()) {
            newOut.set.removeAll(var2Defs.get(def.getRegister().toString()));
        }
        if (!q.getDefinedRegisters().isEmpty()){
            newOut.set.add(q.getID());
        }
        setOut(q, newOut);
    }
```

即先 kill 覆盖的定义，再检查本块是否有定义，有的话 gen



## Faintness

计算非 Faint 变量的方法与计算 Live 非常相像，因此参考 `Liveness` 的实现，计算非 Faint 变量，然后在输出的时候去补集即可。二者的主要区别在于 `processQuad`，代码如下：

```java
    private TransferFunction transferfn = new TransferFunction();

    public void processQuad(Quad q) {
        transferfn.val.copy(out[q.getID()]);
        transferfn.addVal = (NotFaintVarSet) newTempVar();
        Helper.runPass(q, transferfn);
        in[q.getID()].copy(transferfn.val);
    }

    /* The QuadVisitor that actually does the computation */
    public static class TransferFunction extends QuadVisitor.EmptyVisitor {
        NotFaintVarSet val;
        NotFaintVarSet addVal;

        private void addUsed(Quad q) {
            for (Operand.RegisterOperand use : q.getUsedRegisters()) {
                addVal.set.add(use.getRegister().toString());
            }
        }

        private void killDef(Quad q) {
            for (Operand.RegisterOperand def : q.getDefinedRegisters()) {
                val.killVar(def.getRegister().toString());
            }
        }

        @Override
        public void visitMove(Quad q) {
            String dst = Operator.Move.getDest(q).getRegister().toString();
            if (val.set.contains(dst)) {
                addUsed(q);
            }
        }

        @Override
        public void visitBinary(Quad q) {
            String dst = Operator.Binary.getDest(q).getRegister().toString();
            if (val.set.contains(dst)) {
                addUsed(q);
            }
        }

        @Override
        public void visitQuad(Quad q) {
            killDef(q);
            Operator operator = q.getOperator();
            if (!((operator instanceof Operator.Move) || (operator instanceof Operator.Binary))) {
                addUsed(q);
            }
            val.set.addAll(addVal.set);
        }
    }
```

根据要求，仅特殊处理 `Move` 和 `Binaray`，在这两种情况下检查赋值对象是否 not faint，如果是的话，将源操作数加入待加入 not faint 集合 `addVal`。而对于所有的基本快（`QuadVisitor` 会对所有块执行`visitQuad`，即使单独定义过对它们的处理），首先 kill 新的 def，然后判断如果不是 `Move` 或 `Binaray` 的话就在 `addVal` 中加入所有 `used`，最后将 `addVal` 加入 `val` 形成新的 `in`。

值得说明的是，这里需要专门加入 `addVal` 进行一个缓存，而不能像 `Liveness` 一样先 kill 后 gen，原因在于 not faint 相比 live 要求传递性，即只有赋值对象 not faint 的时候操作数才是 not faint，需要 kill 前的信息判断是否加入。如  `x = y` 这一句，其中 `x`  not faint，如果先执行 kill，那么在计算加入集合变量时就会认为 `x` 是 faint，出现问题。



## TestFaintness

首先加入 readme 中的例子，但是因为会被优化为 `return 1`，因此进行修改

```java
    int test2(int t) {
        int x = t; // x not faint
        int y = x + 2; // y faint
        int z = x + y; // z faint
        return x;  // x not faint
    }
```

与 readme 中描述一致，不再赘述

然后测试一些前两个测试中没有出现的情况

```java
    void f_empty(int t) {
    }

	void test3(int t) {
        int x = t;
        int y = -x;  // y faint; x not faint since we don't handle unary operation
        int z = t;
        f_empty(z);  // z not faint since we don't handle invoke
        int a = t;
        int[] b = new int[a]; // b faint; a not faint since we don't handle newarray
    }
```

如单目运算、调用函数、新建数组等，因为它们没被特殊处理，所以即使应该是 faint 也会输出为非faint