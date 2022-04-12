package submit;

// some useful things to import. add any additional imports you need.

import joeq.Compiler.Quad.*;
import flow.Flow;

import java.util.Collection;
import java.util.HashSet;
import java.util.TreeSet;

/**
 * Skeleton class for implementing the Flow.Solver interface.
 */
public class MySolver implements Flow.Solver {

    protected Flow.Analysis analysis;
    private boolean forward;

    /**
     * Sets the analysis.  When visitCFG is called, it will
     * perform this analysis on a given CFG.
     *
     * @param analyzer The analysis to run
     */
    public void registerAnalysis(Flow.Analysis analyzer) {
        this.analysis = analyzer;
        forward = analysis.isForward();
    }

    /**
     * Runs the solver over a given control flow graph.  Prior
     * to calling this, an analysis must be registered using
     * registerAnalysis
     *
     * @param cfg The control flow graph to analyze.
     */
    public void visitCFG(ControlFlowGraph cfg) {

        // this needs to come first.
        analysis.preprocess(cfg);

        /***********************
         * Your code goes here *
         ***********************/

        Quad entryQ = null;
        HashSet<Quad> exitQ = new HashSet<>();
        for (QuadIterator qit = new QuadIterator(cfg); qit.hasNext(); ) {
            Quad q = qit.next();
            if (qit.predecessors1().contains(null)) {
                entryQ = q;
            }
            if (qit.successors1().contains(null)) {
                exitQ.add(q);
            }
        }
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

        // this needs to come last.
        analysis.postprocess(cfg);
    }


    private Flow.DataflowObject meet(Collection<Quad> qs, Flow.DataflowObject beginningData) {
        Flow.DataflowObject res = analysis.newTempVar();
        for (Quad q : qs) {
            Flow.DataflowObject qData;
            if (q == null) {  // entry or exit
                qData = beginningData;
            } else {
                qData = forward ? analysis.getOut(q) : analysis.getIn(q);
            }
            res.meetWith(qData);
        }
        return res;
    }
}
