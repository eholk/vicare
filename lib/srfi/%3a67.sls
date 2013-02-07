;;;Copyright 2010 Derick Eddington.  My MIT-style license is in the file
;;;named LICENSE from  the original collection this  file is distributed
;;;with.

#!r6rs
(library (srfi :67)
  (export
    </<=?
    </<?
    <=/<=?
    <=/<?
    <=?
    <?
    =?
    >/>=?
    >/>?
    >=/>=?
    >=/>?
    >=?
    >?
    boolean-compare
    chain<=?
    chain<?
    chain=?
    chain>=?
    chain>?
    char-compare
    char-compare-ci
    compare-by<
    compare-by<=
    compare-by=/<
    compare-by=/>
    compare-by>
    compare-by>=
    complex-compare
    cond-compare
    debug-compare
    default-compare
    if-not=?
    if3
    if<=?
    if<?
    if=?
    if>=?
    if>?
    integer-compare
    kth-largest
    list-compare
    list-compare-as-vector
    max-compare
    min-compare
    not=?
    number-compare
    pair-compare
    pair-compare-car
    pair-compare-cdr
    pairwise-not=?
    rational-compare
    real-compare
    refine-compare
    select-compare
    string-compare
    string-compare-ci
    symbol-compare
    vector-compare
    vector-compare-as-list)
  (import (srfi :67 compare-procedures)))

;;; end of file
