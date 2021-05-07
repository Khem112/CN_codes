var mongoose = require("mongoose");
const crypto = require("crypto");
const uuidv1 = require("uuid/v1");

var userSchema = new mongoose.Schema(
    {
        username: {
            type: String,
            required: true,
            maxlength: 32,
            unique: true,
            trim: true
        },
        email: {
            type: String,
            trim: true,
            required: true,
            unique: true
        },
        mobile_no: {
            type: String,
            trim: true,
            required: true,
            unique: true
        },
        encry_password: {
            type: String,
            required: true
        },
        salt: String,
        role: {
            type: Number,
            default: 0
        },
        /*
            contest ids we'll store here so that api/contest_id/user_id will give you teams created by user
            updated after every successful team creation
        */
        contests: {
            type: Array,
            default: []
        },
        is_verified_customer: {
            type: Boolean,
            default: false,
        },
        /*
            All wallet details below
            withdrawable_cash - winnings
            deposited_cash - cash earned or deposited
            super_cash - sort of bonuses earned by sign up or as a gift to user
        */
        withdrawable_cash: {
            type: Number,
            min: [0, 'Balance cannot be negative'],
            default: 0,
        },
        deposited_cash: {
            type: Number,
            min: [0, 'Balance cannot be negative'],
            default: 0,
        },
        super_cash: {
            type: Number,
            min: [0, 'Balance cannot be negative'],
            default: 0,
        },
        recent_payments: {
            type: Array,
            default: []
        }
    },
    { timestamps: true }
);

userSchema
    .virtual("password")
    .set(function (password) {
        this._password = password;
        this.salt = uuidv1();
        this.encry_password = this.securePassword(password);
    })
    .get(function () {
        return this._password;
    });

userSchema.methods = {
    autheticate: function (plainpassword) {
        return this.securePassword(plainpassword) === this.encry_password;
    },

    securePassword: function (plainpassword) {
        if (!plainpassword) return "";
        try {
            return crypto
                .createHmac("sha256", this.salt)
                .update(plainpassword)
                .digest("hex");
        } catch (err) {
            return "";
        }
    }
};

const User = mongoose.model("User", userSchema);
module.exports = { User }