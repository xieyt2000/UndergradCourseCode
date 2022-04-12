package submit;

import flow.Flow;
import flow.FlowSolver;
import joeq.Class.jq_Class;
import joeq.Compiler.Quad.*;
import joeq.Main.Helper;

import java.util.*;

public class FindRedundantNullChecks {

    /**
     * Main method of FindRedundantNullChecks.
     * This method should print out a list of quad ids of redundant null checks for each function.
     * The format should be "method_name id0 id1 id2", integers for each id separated by spaces.
     *
     * @param args an array of class names
     */
    public static void main(String[] args) {
        // DONE: Fill in this, like:
        FlowSolver solver = new FlowSolver();
        for (String name : args) {
            jq_Class clazz = (jq_Class) Helper.load(name);
            Flow.Analysis analysis = new PrintRedundant();
            solver.registerAnalysis(analysis);
            Helper.runPass(clazz, solver);
        }
    }
}

class PrintRedundant implements Flow.Analysis {
    private static class CheckedVarSet implements Flow.DataflowObject {
        private static TreeSet<String> universalSet;
        private TreeSet<String> set;

        CheckedVarSet() {
            set = new TreeSet<>(universalSet);
        }

        CheckedVarSet(TreeSet<String> s) {
            set = new TreeSet<>(s);
        }

        @Override
        public void setToTop() {
        }

        @Override
        public void setToBottom() {
        }

        @Override
        public void meetWith(Flow.DataflowObject o) {
            set.retainAll(((CheckedVarSet) o).set);
        }

        @Override
        public void copy(Flow.DataflowObject o) {
            set = new TreeSet<>(((CheckedVarSet) o).set);
        }

        public CheckedVarSet getCopy() {
            CheckedVarSet ret = new CheckedVarSet();
            ret.copy(this);
            return ret;
        }


        @Override
        public boolean equals(Object o) {
            if (o instanceof CheckedVarSet) {
                CheckedVarSet a = (CheckedVarSet) o;
                return set.equals(a.set);
            }
            return false;
        }

        @Override
        public int hashCode() {
            return set.hashCode();
        }

        @Override
        public String toString() {
            return set.toString();
        }
    }

    private CheckedVarSet[] in, out;
    private CheckedVarSet entry, exit;
    private TreeSet<Integer> redundantIds;


    @Override
    public void preprocess(ControlFlowGraph cfg) {
        // this line must come first.

        System.out.print(cfg.getMethod().getName().toString());

        // get the amount of space we need to allocate for the in/out arrays.
        QuadIterator qit = new QuadIterator(cfg);
        int max = 0;
        while (qit.hasNext()) {
            int id = qit.next().getID();
            if (id > max)
                max = id;
        }
        max += 1;

        // Begin computing the universal set.
        TreeSet<String> s = new TreeSet<String>();
        CheckedVarSet.universalSet = s;

        /* Arguments are always there. */
        int numargs = cfg.getMethod().getParamTypes().length;
        for (int i = 0; i < numargs; i++) {
            s.add("R" + i);
        }

        qit = new QuadIterator(cfg);
        while (qit.hasNext()) {
            Quad q = qit.next();
            for (Operand.RegisterOperand def : q.getDefinedRegisters()) {
                s.add(def.getRegister().toString());
            }
            for (Operand.RegisterOperand use : q.getUsedRegisters()) {
                s.add(use.getRegister().toString());
            }
        }
        // End computing the universal set

        // allocate the in and out arrays.
        in = new CheckedVarSet[max];
        out = new CheckedVarSet[max];

        // initialize the contents of in and out.
        qit = new QuadIterator(cfg);
        while (qit.hasNext()) {
            int id = qit.next().getID();
            in[id] = new CheckedVarSet();
            out[id] = new CheckedVarSet();
        }

        // initialize the entry and exit points.
        entry = new CheckedVarSet(new TreeSet<String>());
        exit = new CheckedVarSet();

        redundantIds = new TreeSet<>();
    }

    @Override
    public void postprocess(ControlFlowGraph cfg) {
        for (Integer i : redundantIds) {
            System.out.print(" " + i);
        }
        System.out.println();
        QuadIterator qit = new QuadIterator(cfg);
        while (qit.hasNext()) {
            Quad q = qit.next();
            if (redundantIds.contains(q.getID())) {
                qit.remove();
            }
        }
    }

    @Override
    public boolean isForward() {
        return true;
    }

    @Override
    public Flow.DataflowObject getEntry() {
        return entry.getCopy();
    }

    @Override
    public void setEntry(Flow.DataflowObject value) {
        entry.copy(value);
    }

    @Override
    public Flow.DataflowObject getExit() {
        return exit.getCopy();
    }

    @Override
    public void setExit(Flow.DataflowObject value) {
        exit.copy(value);
    }

    @Override
    public Flow.DataflowObject getIn(Quad q) {
        return in[q.getID()].getCopy();
    }

    @Override
    public Flow.DataflowObject getOut(Quad q) {
        return out[q.getID()].getCopy();
    }

    @Override
    public void setIn(Quad q, Flow.DataflowObject value) {
        in[q.getID()].copy(value);
    }

    @Override
    public void setOut(Quad q, Flow.DataflowObject value) {
        out[q.getID()].copy(value);
    }

    @Override
    public Flow.DataflowObject newTempVar() {
        return new CheckedVarSet();
    }

    @Override
    public void processQuad(Quad q) {
        CheckedVarSet val = (CheckedVarSet) getIn(q);
        int id = q.getID();
        for (Operand.RegisterOperand def : q.getDefinedRegisters()) {
            val.set.remove(def.getRegister().toString());
        }
        if (q.getOperator() instanceof Operator.NullCheck) {
            for (Operand.RegisterOperand use : q.getUsedRegisters()) {  // TODO
                String regStr = use.getRegister().toString();
                if (val.set.contains(regStr)) {
                    redundantIds.add(id);
                } else {
                    redundantIds.remove(id);
                }
                val.set.add(regStr);
            }
        }
        setOut(q, val);
    }
}