var mongoose = require('mongoose');

const { ObjectId } = mongoose.Schema;

const cryptoTeamSchema = new mongoose.Schema({
    crypto: {
        type: ObjectId,
        ref: "Crypto"
    },
    starting_price: {
        type: Number,
        default: 0,
    },
    current_price: {
        type: Number,
        default: 0,
    },
    final_price: {
        type: Number,
        default: 0
    }
})

const CryptoTeam = mongoose.model("CryptoTeam", cryptoTeamSchema);

var teamSchema = new mongoose.Schema({
    cryptos: [cryptoTeamSchema],
    team_id: {},
    user: {
        type: ObjectId,
        ref: "User"
    },
    contest: {
        type: ObjectId,
        ref: "Contest"
    },
    captain: {
        type: ObjectId,
        ref: "Crypto"
    },
    viceCaptain: {
        type: ObjectId,
        re: "Crypto"
    },
    NFT_cnt: {
        type: Number,
        default: 0,
    },
    Defi_cnt: {
        type: Number,
        default: 0
    },
    Alt_cnt: {
        type: Number,
        default: 0
    }
},
    { timestamps: true }
)

const Team = mongoose.model("Team", teamSchema);
module.exports = { Team, CryptoTeam };