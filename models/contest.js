var mongoose = require("mongoose");

var prizeSchema = new mongoose.Schema({
    fromRank: {
        type: Number,
        required: true
    },
    toRank: {
        type: Number,
        required: true,
    },
    amount: {
        type: Number,
        required: true,
        min: [0, 'Amount cannot be negative'],
    }
});

const Prize = mongoose.model("Prize", prizeSchema);

var contestSchema = new mongoose.Schema({
    contestId: {
    },
    startTime: {
        type: Date,
        required: true
    },
    endTime: {
        type: Date,
        required: true
    },
    totalWinners: {
        type: Number,
        default: 0
    },
    totalPrizeMoney: {
        type: Number,
        default: 0,
    },
    contestDate: {
        type: Date,
        required: true
    },
    contestType: {
        type: Number,
        default: 2
    },
    maxAllowedTeams: {
        type: Number,
        default: 1
    },
    currentJoinedTeams: {
        type: Number,
        default: 0
    },
    entryFee: {
        type: Number,
        default: 0
    },
    maxBonusUsable: {
        type: Number,
        default: 0
    },
    maxTeamsAllowedForUser: {
        type: Number,
        default: 1
    },
    adminApprovedStatus: {
        type: Number,
        /*
            (1-cancelled,2-complete,3-live,4-upcoming)
        */
        default: 4
    },
    winners: {
        type: Array,
        default: []
    },
    prizeArray: {
        type: [prizeschema]
    }
});

const Contest = mongoose.model("Contest", contestSchema);
module.exports = { Prize, Contest }